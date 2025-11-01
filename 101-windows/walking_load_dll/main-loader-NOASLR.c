#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *setup_dll(long *dll_size)
{
    const char *path = ".\\bin\\dllmock.dll";

    FILE *f = fopen(path, "rb");
    if (!f)
    {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END); // Mueve el puntero del fichero
    long size = ftell(f);  // Devuelve la posición actual del puntero
    fseek(f, 0, SEEK_SET); // Mueve el puntero del fichero al principio

    unsigned char *buffer = malloc(size); // Reservar memoria en el heap
    if (!buffer)
    {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fread(
        buffer, // Dirección de memoria donde se almacenarán los bytes leídos del archivo
        1,      // Tamaño de cada elemento a leer en bytes (1 byte por elemento)
        size,   // Número de elementos a leer (en total se leerán 'size' bytes)
        f       // Puntero al archivo abierto desde el que se leerán los datos
    );

    fclose(f);

    printf("PE de la DLL cargada en memoria, tamanyo: %ld bytes, direccion: %p\n", size, (void *)buffer);
    *dll_size = size;
    return buffer;
}

static void print_hex32(const char *label, DWORD v)
{
    printf("  %-24s 0x%08X (%u)\n", label, (unsigned)v, (unsigned)v);
}

int main(void)
{
    printf("; ============================================================\n");
    printf(";       MY DLL LOADER (x64)\n");
    printf("; ============================================================\n");

    // ------------------------------------------------------------
    // Cargamos en memoria la dll
    long dll_size = 0;
    void *RawData = setup_dll(&dll_size);


    // ------------------------------------------------------------
    // Parsear headers PE
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)RawData;
    const size_t nt_offset = (size_t)dos->e_lfanew;
    const IMAGE_NT_HEADERS *nt = (const IMAGE_NT_HEADERS *)(RawData + nt_offset);
    const IMAGE_FILE_HEADER *filehdr = &nt->FileHeader;

    const unsigned char *optional_ptr = (const unsigned char *)&nt->OptionalHeader;
    const WORD optMagic = *(const WORD *)optional_ptr;
    const int is64 = (optMagic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);

    if (!is64){exit (1);}

    const IMAGE_OPTIONAL_HEADER64 *optional_header = (const IMAGE_OPTIONAL_HEADER64 *)optional_ptr;
    const IMAGE_SECTION_HEADER *sections = (const IMAGE_SECTION_HEADER *)(optional_ptr + filehdr->SizeOfOptionalHeader);

    // ------------------------------------------------------------
    // Reservar memoria en el proceso para la DLL (OptionalHeader.SizeOfImage)
    // Como esto es una version NO ASLR, reservamos en la misma direccion que el ImageBase original
    DWORD SizeOfImage = (DWORD)optional_header->SizeOfImage;

    uintptr_t ImageBase = VirtualAlloc(
        optional_header->ImageBase,     // dirección preferida (NULL = sistema elige)
        SizeOfImage,                    // tamaño en bytes
        MEM_COMMIT | MEM_RESERVE,       // reservar y comprometer
        PAGE_EXECUTE_READWRITE          // permisos (ejecutable + lectura + escritura)
    );

    if (ImageBase == NULL)
    {
        printf("VirtualAlloc failed: %u\n", GetLastError());
        return 1;
    }

    printf("Memory allocated at: %p\n", ImageBase);


    // ------------------------------------------------------------
    // Copiar cabeceras PE (SizeOfHeaders)
    DWORD SizeOfHeaders = (DWORD)optional_header->SizeOfHeaders;
    memcpy(ImageBase, RawData, SizeOfHeaders); // memcpy(destino, origen, tamaño)

    // ------------------------------------------------------------
    // Mapear las Secciones
    //      - Destino: destino = ImageBase + section[i].VirtualAddress
    //      - Origen: origen = BufferDelArchivo + section[i].PointerToRawData
    //      - Tamaño: tamaño = section[i].SizeOfRawData
    // .bss (o si PointerToRawData es 0), no copiar. En su lugar, usa memset(destino, 0, section[i].VirtualSize) para llenar esa sección de ceros.
    WORD NumberOfSections = (WORD)filehdr->NumberOfSections;
    printf("=== SECTION HEADERS (count=%u) ===\n", NumberOfSections);
    for (DWORD i = 0; i < NumberOfSections; ++i)
    {
        char name[9] = {0};
        memcpy(name, sections[i].Name, 8);
        printf("  [%2u] %-8s  VirtualSize=0x%08X  VirtualAddress=0x%08X  SizeOfRawData=0x%08X  PointerToRawData=0x%08X  Characteristics=0x%08X\n",
                (unsigned)i,
                name,
                sections[i].Misc.VirtualSize,
                sections[i].VirtualAddress,
                sections[i].SizeOfRawData,
                sections[i].PointerToRawData,
                sections[i].Characteristics);
        
        if (sections[i].PointerToRawData == 0)
        {
            // .bss o sección sin datos en el archivo
            memset(ImageBase + sections[i].VirtualAddress, 0, sections[i].Misc.VirtualSize);
            continue;
        }
        
        memcpy(ImageBase + sections[i].VirtualAddress, RawData + sections[i].PointerToRawData, sections[i].Misc.VirtualSize); // memcpy(destino, origen, tamaño)
    }

    // ------------------------------------------------------------
    // IMPORTANTE: A partir de aquí, la DLL ya está "mapeada" en memoria, pero NO está lista para ejecutarse.
    // Hay que procesar las RELOCACIONES y las IMPORTACIONES.
    // ------------------------------------------------------------
    // Ahora que la DLL está mapeada en ImageBase, obtenemos los punteros a las cabeceras desde ahí.
    const IMAGE_DOS_HEADER *dos_header_mapped = (const IMAGE_DOS_HEADER *)ImageBase;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fprintf(stderr, "[!] Error: Invalid DOS signature (MZ).\n");
        return 0;
    }

    const IMAGE_NT_HEADERS64 *nt_headers_mapped = (const IMAGE_NT_HEADERS64 *)((LPBYTE)ImageBase + dos_header_mapped->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE)
    {
        fprintf(stderr, "[!] Error: Invalid PE signature.\n");
        return 0;
    }

    const IMAGE_OPTIONAL_HEADER64* opt_header_mapped = &nt_headers_mapped->OptionalHeader;


    // ------------------------------------------------------------
    // Importaciones
    //      - Buscar Tabla .idata: Encuentra la sección .idata que mapeaste.
    //      - Iterar (DLLs): Recorre la tabla. Verás los nombres de las DLLs que necesita (ej. "user32.dll", "kernel32.dll").
    //      - Llamar a LoadLibraryA: Llama a LoadLibraryA (ej. LoadLibraryA("user32.dll")) para cada una.
    //      - Iterar (Funciones): Dentro de cada DLL, recorre la lista de funciones que necesita (ej. "MessageBoxA").
    //      - Llamar a GetProcAddress: Llama a GetProcAddress (ej. GetProcAddress(hUser32, "MessageBoxA")).
    //      - Parchear la IAT: Escribe la dirección de la función devuelta en la Tabla de Direcciones de Importación (IAT) de tu DLL (que también está en la sección .idata).
    printf("=== IMAGE_IMPORT_DESCRIPTOR ===\n");
    
    const DWORD rva_to_idata = opt_header_mapped->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    uintptr_t idata_addr = (uintptr_t)ImageBase + rva_to_idata;
    

    IMAGE_IMPORT_DESCRIPTOR* import_descriptor = (IMAGE_IMPORT_DESCRIPTOR *)idata_addr;

    while (import_descriptor->Name != 0)
    {
        print_hex32("Name RVA", import_descriptor->Name);
        print_hex32("OriginalFirstThunk RVA", import_descriptor->OriginalFirstThunk);
        print_hex32("FirstThunk (IAT) RVA", import_descriptor->FirstThunk);

        char *dll_name = (char *)(ImageBase + import_descriptor->Name);
        printf("\nDLL: %s\n", dll_name);

        // Puntero al array de Nombres (OriginalFirstThunk)
        PIMAGE_THUNK_DATA oft_thunk = (PIMAGE_THUNK_DATA)(ImageBase + import_descriptor->OriginalFirstThunk);
        
        // Puntero al array de Direcciones (FirstThunk / IAT)
        PIMAGE_THUNK_DATA iat_thunk = (PIMAGE_THUNK_DATA)(ImageBase + import_descriptor->FirstThunk);

        uintptr_t import_handle = LoadLibraryA(dll_name);
        if (import_handle == NULL) {
            printf("  -> ERROR: No se pudo cargar %s\n", dll_name);
            import_descriptor++;
            continue; // Salta a la siguiente DLL
        }


        while (oft_thunk->u1.AddressOfData != 0) {
            // 1. Obtiene el nombre de la función desde el OFT
            PIMAGE_IMPORT_BY_NAME import_by_name = (PIMAGE_IMPORT_BY_NAME)(ImageBase + oft_thunk->u1.AddressOfData);

            // 2. Obtiene la dirección de memoria real desde la IAT
            //    (iat_thunk->u1.Function ES la dirección)
            uintptr_t function_address = (uintptr_t)iat_thunk->u1.Function;

            uintptr_t real_address = GetProcAddress((HMODULE)import_handle, (LPCSTR)import_by_name->Name);

            iat_thunk->u1.Function = real_address;

            printf("  -> Funcion: %-30s (Parcheada en: %p)\n", (char *)import_by_name->Name, (void*)real_address);     
                  
            oft_thunk++;
            iat_thunk++;
        }
        
        // Avanza al siguiente descriptor (siguiente DLL)
        import_descriptor++;
    }

    printf("\n");
    
    // Relocaciones
    //      - Calcular Delta: delta = NuevaImageBase - ImageBaseOriginal
    //      - Buscar Tabla .reloc: Encuentra la sección .reloc que acabas de mapear.
    //      - Iterar: Recorre esta tabla (que es una serie de bloques) y "parchea" cada dirección absoluta en tu código (.text, .data) sumándole el delta.


    // ------------------------------------------------------------
    // call new entry point, DllMain with DLL_PROCESS_ATTACH
    //      - ImageBase + AddressOfEntryPoint
    DWORD entryPointRVA = optional_header->AddressOfEntryPoint;

    // Si el EntryPoint es 0, la DLL no tiene DllMain (ej. DLL de solo recursos)
    if (entryPointRVA == 0) {
        printf("La DLL no tiene punto de entrada (EntryPoint).\n");
        return 1;
    }

    // Definir el prototipo (firma) de la función DllMain
    typedef BOOL (WINAPI *PFN_DLLMAIN)(
        HINSTANCE hinstDLL,
        DWORD     fdwReason,
        LPVOID    lpvReserved
    );

    // Calcular la dirección de memoria ABSOLUTA del punto de entrada
    uintptr_t entryPointAbsolute = (uintptr_t)ImageBase + entryPointRVA;

    // Hacer un "cast" de esa dirección numérica a nuestro tipo de puntero de función
    PFN_DLLMAIN DllMain = (PFN_DLLMAIN)entryPointAbsolute;

    printf("Llamando a DllMain en la dirección: %p\n", (void*)DllMain);

    // Llamar a la función
    //    - El HMODULE/HINSTANCE es la propia ImageBase.
    //    - La "razón" es DLL_PROCESS_ATTACH.
    //    - lpvReserved es NULL para esta llamada.
    DllMain((HINSTANCE)ImageBase, DLL_PROCESS_ATTACH, NULL);

    // Cerrar handles sólo cuando existen
    printf("Pulsa ENTER para terminar\n");
    getchar();
    free(RawData);
    return 0;
}