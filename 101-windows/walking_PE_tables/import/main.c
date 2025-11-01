#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#define OFFSET_E_LFANEW              0x3C
#define OFFSET_EXPORT_DIRECTORY      0x78
#define OFFSET_EXPORT_NAME           0x0C
#define OFFSET_NUMBER_OF_FUNCTIONS   0x14
#define OFFSET_ADDRESS_OF_FUNCTIONS  0x1C
#define OFFSET_ADDRESS_OF_NAMES      0x20
#define OFFSET_ADDRESS_OF_NAME_ORDS  0x24

#pragma comment(lib, "ws2_32.lib")

// ------------------------------------------------------------
// Utilidad: leer un valor DWORD desde una dirección base
static uint32_t read_dword(const uint8_t *base, uintptr_t offset) {
    return *(const uint32_t *)(base + offset);
}

// ------------------------------------------------------------
// Obtiene la dirección del Export Directory de un módulo
static uint8_t *get_export_directory(uint8_t *base_address) {
    if (!base_address) return NULL;

    uint32_t e_lfanew = read_dword(base_address, OFFSET_E_LFANEW);
    if (!e_lfanew) return NULL;

    uint8_t *nt_headers = base_address + e_lfanew;
    uint32_t rva_export_directory = read_dword(nt_headers, OFFSET_EXPORT_DIRECTORY);

    if (!rva_export_directory) return NULL;

    return base_address + rva_export_directory;
}

static void get_idata_address(uint8_t *base_address) {
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)base_address;
    const IMAGE_NT_HEADERS64 *nt = (const IMAGE_NT_HEADERS64 *)(base_address + dos->e_lfanew);
    const IMAGE_FILE_HEADER *filehdr = &nt->FileHeader;
    const IMAGE_OPTIONAL_HEADER64 *opt64 = &nt->OptionalHeader;

    const DWORD *rva_to_reloc = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
}

// ------------------------------------------------------------
// Imprime información de exports de un módulo
static void print_relocs(uint8_t *base_address) {
    // Nivel 1: El Array de DLLs (IMAGE_IMPORT_DESCRIPTOR)
    // Nivel 2: Los Arrays Paralelos (OFT y IAT)
    // Nivel 3: Los Nombres de las Funciones (IMAGE_IMPORT_BY_NAME)
    rva_to_iat = 0x00008A00; // (DISCO) En un caso real usar memoria mapeada
    
    printf("=== IMAGE_IMPORT_DESCRIPTOR ===\n");
    
    //  1 IMAGE_IMPORT_DESCRIPTOR por cada dll
    IMAGE_IMPORT_DESCRIPTOR* import_descriptor = (IMAGE_IMPORT_DESCRIPTOR*)((unsigned char*)base + rva_to_iat);
    print_hex32("Name", import_descriptor->Name);
    print_hex32("OriginalFirstThunk", import_descriptor->OriginalFirstThunk);
    print_hex32("FirstThunk", import_descriptor->FirstThunk);
    // OriginalFirstThunk y FirstThunk son dos arrays paralelos (listas) de punteros (uintptr_t)
    // Ambos tienen el mismo tamaño y están terminados por un NULL.
        // OriginalFirstThunk (OFT): La Lista de Nombres.
            // cada posicion es un RVA a IMAGE_IMPORT_BY_NAME
        // FirstThunk (IAT): La Lista de Punteros.

    while (import_descriptor->Name != 0) 
    {
        // NO FUNCIONA ESTO ES PARA MEMORIA Y ESTAMOS EN DISCO

        // El RVA 'Name' apunta a un string (char*)
        char* dll_name = (char*)((unsigned char*)base + import_descriptor->Name);
        printf("\nDLL: %s\n", dll_name);
        
        // Imprimimos la información del descriptor
        print_hex32("Name RVA", import_descriptor->Name);
        print_hex32("OriginalFirstThunk RVA", import_descriptor->OriginalFirstThunk);
        print_hex32("FirstThunk (IAT) RVA", import_descriptor->FirstThunk);

        // 2. Apuntamos al inicio del array OriginalFirstThunk (OFT)
        //    (Este array contiene RVAs a los nombres de las funciones)
        PIMAGE_THUNK_DATA thunk_data = 
            (PIMAGE_THUNK_DATA)((unsigned char*)base + import_descriptor->OriginalFirstThunk);

        // --- BUCLE INTERNO (Itera sobre cada FUNCIÓN de esta DLL) ---
        // Este array termina cuando el puntero (AddressOfData) es 0 (NULL)
        while (thunk_data->u1.AddressOfData != 0) 
        {
            // 3. El 'AddressOfData' es un RVA a una estructura IMAGE_IMPORT_BY_NAME
            PIMAGE_IMPORT_BY_NAME import_by_name = 
                (PIMAGE_IMPORT_BY_NAME)((unsigned char*)base + thunk_data->u1.AddressOfData);
            
            // --- (Imprime el nombre de la función) ---
            // El campo 'Name' es el string de la función
            printf("  -> Funcion: %s\n", (char*)import_by_name->Name);

            // Avanzamos al siguiente thunk (siguiente función)
            thunk_data++;
        }

        // Avanzamos al siguiente descriptor (siguiente DLL)
        import_descriptor++;
    }

    printf("\n");
}

// ------------------------------------------------------------
int main(void) {
    printf("; ============================================================\n");
    printf(";   x64 TABLA DE IMPORTS \n");
    printf("; ============================================================\n");

    const char *ws2_32 = "ws2_32.dll";
    const char *kernel32 = "kernel32.dll";


    HMODULE module_handle = LoadLibraryA(kernel32);
    if (!module_handle) {
        fprintf(stderr, "[!] Error: no se pudo cargar %s\n", kernel32);
        return 1;
    }

    printf("Module handle: %p\n", (void *)module_handle);

    print_exports((uint8_t *)module_handle);

    FreeLibrary(module_handle);

    return 0;
}
