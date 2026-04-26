#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#define OFFSET_E_LFANEW 0x3C
#define OFFSET_EXPORT_DIRECTORY 0x78
#define OFFSET_EXPORT_NAME 0x0C
#define OFFSET_NUMBER_OF_FUNCTIONS 0x14
#define OFFSET_ADDRESS_OF_FUNCTIONS 0x1C
#define OFFSET_ADDRESS_OF_NAMES 0x20
#define OFFSET_ADDRESS_OF_NAME_ORDS 0x24

#pragma comment(lib, "ws2_32.lib")


static void print_hex32(const char *label, DWORD v)
{
    printf("  %-24s 0x%08X (%u)\n", label, (unsigned)v, (unsigned)v);
}

static size_t get_idata_address(uintptr_t base_address)
{
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)base_address;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fprintf(stderr, "[!] Error: Invalid DOS signature (MZ).\n");
        return 0;
    }

    const IMAGE_NT_HEADERS64 *nt = (const IMAGE_NT_HEADERS64 *)(base_address + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE)
    {
        fprintf(stderr, "[!] Error: Invalid PE signature.\n");
        return 0;
    }

    const IMAGE_OPTIONAL_HEADER64 *opt64 = &nt->OptionalHeader;

    const DWORD rva_to_idata = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

    return base_address + rva_to_idata;
}

// ------------------------------------------------------------
// 
static void print_idata(uintptr_t module_handle, uintptr_t idata_addr)
{
    printf("=== IMAGE_IMPORT_DESCRIPTOR ===\n");

    IMAGE_IMPORT_DESCRIPTOR* import_descriptor = (IMAGE_IMPORT_DESCRIPTOR *)idata_addr;

    while (import_descriptor->Name != 0)
    {
        print_hex32("Name RVA", import_descriptor->Name);
        print_hex32("OriginalFirstThunk RVA", import_descriptor->OriginalFirstThunk);
        print_hex32("FirstThunk (IAT) RVA", import_descriptor->FirstThunk);

        char *dll_name = (char *)(module_handle + import_descriptor->Name);
        printf("\nDLL: %s\n", dll_name);

        // Puntero al array de Nombres (OriginalFirstThunk)
        PIMAGE_THUNK_DATA oft_thunk = (PIMAGE_THUNK_DATA)(module_handle + import_descriptor->OriginalFirstThunk);
        
        // Puntero al array de Direcciones (FirstThunk / IAT)
        PIMAGE_THUNK_DATA iat_thunk = (PIMAGE_THUNK_DATA)(module_handle + import_descriptor->FirstThunk);

        while (oft_thunk->u1.AddressOfData != 0) {
            // 1. Obtiene el nombre de la función desde el OFT
            PIMAGE_IMPORT_BY_NAME import_by_name = (PIMAGE_IMPORT_BY_NAME)(module_handle + oft_thunk->u1.AddressOfData);

            // 2. Obtiene la dirección de memoria real desde la IAT
            //    (iat_thunk->u1.Function ES la dirección)
            uintptr_t function_address = (uintptr_t)iat_thunk->u1.Function;

            printf("  -> Funcion: %-30s (Address: %p)\n", (char *)import_by_name->Name, (void*)function_address);
            
            oft_thunk++;
            iat_thunk++;
        }
        
        // Avanza al siguiente descriptor (siguiente DLL)
        import_descriptor++;
    }

    printf("\n");
}

// ------------------------------------------------------------
int main(void)
{
    printf("; ============================================================\n");
    printf(";   x64 TABLA DE IMPORTS \n");
    printf("; ============================================================\n");

    const char *ws2_32 = "ws2_32.dll";
    const char *kernel32 = "kernel32.dll";

    uintptr_t module_handle = LoadLibraryA(kernel32);

    if (!module_handle)
    {
        fprintf(stderr, "[!] Error: no se pudo cargar %s\n", kernel32);
        return 1;
    }

    printf("Module handle: %p\n", (void *)module_handle);

    uintptr_t idata_addr = get_idata_address(module_handle);

    print_idata(module_handle, idata_addr);

    FreeLibrary(module_handle);
    return 0;
}
