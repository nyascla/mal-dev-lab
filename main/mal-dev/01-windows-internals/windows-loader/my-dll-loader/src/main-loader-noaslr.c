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
    long size = ftell(f);  // Devuelve la posición actual del puntero (tamaño del archivo)
    fseek(f, 0, SEEK_SET); // Mueve el puntero del fichero al principio

    unsigned char *buffer = malloc(size); // Reservar memoria en el heap
    if (buffer == NULL)
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

static BOOL resolve_imports(LPVOID ImageBase)
{
    const IMAGE_DOS_HEADER *dos_header = (const IMAGE_DOS_HEADER *)ImageBase;
    const IMAGE_NT_HEADERS64 *nt_headers = (const IMAGE_NT_HEADERS64 *)((LPBYTE)ImageBase + dos_header->e_lfanew);
    const IMAGE_OPTIONAL_HEADER64 *opt_header = &nt_headers->OptionalHeader;

    // Obtener la RVA de la tabla de importaciones (.idata)
    IMAGE_DATA_DIRECTORY import_dir = opt_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (import_dir.VirtualAddress == 0)
    {
        printf("La DLL no tiene tabla de importaciones.\n");
        return TRUE; // No es un error, simplemente no hay nada que hacer.
    }

    printf("=== RESOLVIENDO IMPORTACIONES (.idata) ===\n");

    IMAGE_IMPORT_DESCRIPTOR *import_descriptor = (IMAGE_IMPORT_DESCRIPTOR *)((LPBYTE)ImageBase + import_dir.VirtualAddress);

    while (import_descriptor->Name != 0)
    {
        char *dll_name = (char *)((LPBYTE)ImageBase + import_descriptor->Name);
        HMODULE h_dll = LoadLibraryA(dll_name);
        if (h_dll == NULL)
        {
            fprintf(stderr, "  [!] Error: No se pudo cargar la DLL '%s'. Codigo: %lu\n", dll_name, GetLastError());
            return FALSE; // Error crítico, no se puede continuar.
        }
        printf("  DLL: %s (Handle: %p)\n", dll_name, (void *)h_dll);

        // Puntero al array de Nombres (OriginalFirstThunk)
        PIMAGE_THUNK_DATA oft_thunk = (PIMAGE_THUNK_DATA)((LPBYTE)ImageBase + import_descriptor->OriginalFirstThunk);
        // Puntero al array de Direcciones (FirstThunk / IAT)
        PIMAGE_THUNK_DATA iat_thunk = (PIMAGE_THUNK_DATA)((LPBYTE)ImageBase + import_descriptor->FirstThunk);

        while (oft_thunk->u1.AddressOfData != 0)
        {
            // Obtiene el nombre de la función desde el OFT
            PIMAGE_IMPORT_BY_NAME import_by_name = (PIMAGE_IMPORT_BY_NAME)((LPBYTE)ImageBase + oft_thunk->u1.AddressOfData);
            LPCSTR func_name = (LPCSTR)import_by_name->Name;

            // Obtiene la dirección real de la función
            uintptr_t real_address = (uintptr_t)GetProcAddress(h_dll, func_name);
            if (real_address == 0) {
                fprintf(stderr, "    [!] Error: No se pudo encontrar la funcion '%s' en '%s'.\n", func_name, dll_name);
                return FALSE;
            }

            // Parchea la IAT con la dirección real
            iat_thunk->u1.Function = real_address;
            oft_thunk++;
            iat_thunk++;
        }
        import_descriptor++;
    }
    printf("\n");
    return TRUE;
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
    if (RawData == NULL) {
        return 1;
    }

    // ------------------------------------------------------------
    // Parsear headers PE
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)RawData;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) {
        fprintf(stderr, "[!] Error: El archivo no tiene una firma MZ valida.\n");
        free(RawData);
        return 1;
    }

    const IMAGE_NT_HEADERS64 *nt = (const IMAGE_NT_HEADERS64 *)((LPBYTE)RawData + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) {
        fprintf(stderr, "[!] Error: El archivo no tiene una firma PE valida.\n");
        free(RawData);
        return 1;
    }

    if (nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        fprintf(stderr, "[!] Error: El archivo no es un PE de 64 bits.\n");
        free(RawData);
        return 1;
    }

    const IMAGE_OPTIONAL_HEADER64 *optional_header = &nt->OptionalHeader;
    const IMAGE_FILE_HEADER *filehdr = &nt->FileHeader;
    const IMAGE_SECTION_HEADER *sections = IMAGE_FIRST_SECTION(nt);

    // ------------------------------------------------------------
    // Reservar memoria en el proceso para la DLL (OptionalHeader.SizeOfImage)
    // Como esto es una version NO ASLR, reservamos en la misma direccion que el ImageBase original
    DWORD SizeOfImage = (DWORD)optional_header->SizeOfImage;

    LPVOID ImageBase = VirtualAlloc(
        (LPVOID)optional_header->ImageBase,     // dirección preferida (NULL = sistema elige)
        SizeOfImage,                            // tamaño en bytes
        MEM_COMMIT | MEM_RESERVE,               // reservar y comprometer
        PAGE_EXECUTE_READWRITE                  // permisos (ejecutable + lectura + escritura)
    );

    if (ImageBase == NULL)
    {
        printf("VirtualAlloc failed: %u\n", GetLastError());
        free(RawData);
        return 1;
    }

    printf("Memory allocated at: %p\n", ImageBase);

    // ------------------------------------------------------------
    // Copiar cabeceras PE (SizeOfHeaders)
    DWORD SizeOfHeaders = (DWORD)optional_header->SizeOfHeaders;
    memcpy((void*)ImageBase, RawData, SizeOfHeaders); // memcpy(destino, origen, tamaño)

    // ------------------------------------------------------------
    // Mapear las Secciones
    //      - Destino: destino = ImageBase + section[i].VirtualAddress
    //      - Origen: origen = BufferDelArchivo + section[i].PointerToRawData
    //      - Tamaño: tamaño = section[i].SizeOfRawData
    // .bss (o si PointerToRawData es 0), no copiar. En su lugar, usa memset(destino, 0, section[i].VirtualSize) para llenar esa sección de ceros.
    WORD NumberOfSections = (WORD)filehdr->NumberOfSections;
    printf("=== MAPEANDO SECCIONES (count=%u) ===\n", NumberOfSections);
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
        
        LPVOID dest = (LPBYTE)ImageBase + sections[i].VirtualAddress;

        if (sections[i].PointerToRawData == 0)
        {
            // .bss o sección sin datos en el archivo
            if (sections[i].Misc.VirtualSize > 0) {
                memset(dest, 0, sections[i].Misc.VirtualSize);
            }
        }
        else
        {
            // Copiar datos desde el archivo
            memcpy(dest, (LPBYTE)RawData + sections[i].PointerToRawData, sections[i].SizeOfRawData);
        }
    }
    printf("\n");

    // ------------------------------------------------------------
    // Relocaciones (NO IMPLEMENTADO)
    // Como hemos forzado la carga en la ImageBase preferida, no es necesario
    // procesar las relocaciones. Si VirtualAlloc fallara y tuviéramos que
    // cargar en otra dirección, este paso sería CRÍTICO.

    // ------------------------------------------------------------
    // Importaciones
    if (!resolve_imports((LPVOID)ImageBase)) {
        fprintf(stderr, "[!] Error: Fallo al resolver las importaciones.\n");
        VirtualFree((LPVOID)ImageBase, 0, MEM_RELEASE);
        free(RawData);
        return 1;
    }

    // ------------------------------------------------------------
    // Aplicar protecciones de memoria correctas a las secciones
    printf("=== APLICANDO PROTECCIONES DE MEMORIA ===\n");
    for (DWORD i = 0; i < NumberOfSections; ++i) {
        LPVOID section_start = (LPBYTE)ImageBase + sections[i].VirtualAddress;
        DWORD size = sections[i].Misc.VirtualSize;
        DWORD characteristics = sections[i].Characteristics;
        DWORD old_protect;
        DWORD new_protect = 0;

        if (characteristics & IMAGE_SCN_MEM_EXECUTE) {
            new_protect = (characteristics & IMAGE_SCN_MEM_WRITE) ? PAGE_EXECUTE_READWRITE : PAGE_EXECUTE_READ;
        } else {
            new_protect = (characteristics & IMAGE_SCN_MEM_WRITE) ? PAGE_READWRITE : PAGE_READONLY;
        }

        if (!VirtualProtect(section_start, size, new_protect, &old_protect)) {
            fprintf(stderr, "[!] Error: Fallo al proteger la seccion %s. Codigo: %lu\n", sections[i].Name, GetLastError());
        }
    }
    printf("\n");

    // ------------------------------------------------------------
    // call new entry point, DllMain with DLL_PROCESS_ATTACH
    //      - ImageBase + AddressOfEntryPoint
    DWORD entryPointRVA = nt->OptionalHeader.AddressOfEntryPoint;

    // Si el EntryPoint es 0, la DLL no tiene DllMain (ej. DLL de solo recursos)
    if (entryPointRVA == 0) {
        printf("La DLL no tiene punto de entrada (EntryPoint).\n");
        // No es un error, simplemente no hay nada que llamar.
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
    //    - lpvReserved es NULL para esta llamada inicial.
    BOOL success = DllMain((HINSTANCE)ImageBase, DLL_PROCESS_ATTACH, NULL);
    if (!success) {
        fprintf(stderr, "[!] DllMain retorno FALSE en DLL_PROCESS_ATTACH.\n");
    }

    printf("Pulsa ENTER para terminar\n");
    getchar();
    VirtualFree((LPVOID)ImageBase, 0, MEM_RELEASE);
    free(RawData);
    return 0;
}