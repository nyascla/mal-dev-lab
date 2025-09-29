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

// ------------------------------------------------------------
// Imprime información de exports de un módulo
static void print_exports(uint8_t *base_address) {
    if (!base_address) {
        fprintf(stderr, "[!] Error: base_address es NULL\n");
        return;
    }

    uint8_t *export_directory = get_export_directory(base_address);
    if (!export_directory) {
        fprintf(stderr, "[!] Error: no se pudo obtener export directory\n");
        return;
    }

    uint32_t rva_name = read_dword(export_directory, OFFSET_EXPORT_NAME);
    char *dll_name = (char *)(base_address + rva_name);
    printf("DLL Name: %s\n", dll_name);

    uint32_t number_of_functions = read_dword(export_directory, OFFSET_NUMBER_OF_FUNCTIONS);
    printf("Number of functions: %u\n", number_of_functions);

    uint32_t rva_address_of_names = read_dword(export_directory, OFFSET_ADDRESS_OF_NAMES);
    uint32_t rva_address_of_name_ordinals = read_dword(export_directory, OFFSET_ADDRESS_OF_NAME_ORDS);
    uint32_t rva_address_of_functions = read_dword(export_directory, OFFSET_ADDRESS_OF_FUNCTIONS);

    if (!rva_address_of_names || !rva_address_of_name_ordinals || !rva_address_of_functions) {
        fprintf(stderr, "[!] Error: export table incompleta\n");
        return;
    }

    DWORD *address_of_names = (DWORD *)(base_address + rva_address_of_names);
    WORD *address_of_name_ordinals = (WORD *)(base_address + rva_address_of_name_ordinals);
    DWORD *address_of_functions = (DWORD *)(base_address + rva_address_of_functions);

    printf("Exported functions:\n");
    for (size_t i = 0; i < number_of_functions; i++) {
        DWORD name_rva = address_of_names[i];
        if (!name_rva) continue;

        char *function_name = (char *)(base_address + name_rva);
        WORD ordinal = address_of_name_ordinals[i];
        DWORD function_rva = address_of_functions[ordinal];

        printf("    [%02zu] Ordinal: %u - RVA: 0x%lX - Name: %s\n", i, ordinal + 1, function_rva, function_name);
    }
}

// ------------------------------------------------------------
int main(void) {
    printf("; ============================================================\n");
    printf("; x86 LISTADO DE EXPORTS DE UN MÓDULO DLL\n");
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
