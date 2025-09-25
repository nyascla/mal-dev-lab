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


uint32_t rol(uint32_t val, unsigned int r_bits, unsigned int max_bits) {
    r_bits %= max_bits;
    return (val << r_bits) | (val >> (max_bits - r_bits));
}

uint32_t create_hash(const char *export_name) {
    uint32_t result = 0;

    // printf("== Creando hash para '%s' ==\n", export_name);

    for (size_t i = 0; i < strlen(export_name); i++) {
        char ch = tolower((unsigned char)export_name[i]);
        uint32_t before = result;
        result = rol(result, 7, 32);
        uint32_t after_rol = result;
        result ^= (uint32_t)ch;

        // printf("[%zu] char='%c' ascii=%d before=0x%08X after_rol=0x%08X result=0x%08X\n",
        //        i, ch, (int)ch, before, after_rol, result);
    }

    // printf("0x%08X", result);
    return result;
}


// Función para imprimir todos los exports de una DLL cargada
void print_exports(uint8_t *base_address, DWORD x) {
    if (!base_address) {
        fprintf(stderr, "Error: base_address es NULL\n");
        return;
    }

    // Leer e_lfanew desde el DOS header
    uint32_t e_lfanew = *(uint32_t *)(base_address + OFFSET_E_LFANEW);
    if (!e_lfanew) {
        fprintf(stderr, "Error: e_lfanew inválido\n");
        return;
    }

    uint8_t *nt_headers = base_address + e_lfanew;

    // Leer RVA del directorio de exportaciones
    uint32_t rva_export_directory = *(uint32_t *)(nt_headers + OFFSET_EXPORT_DIRECTORY);
    if (!rva_export_directory) {
        fprintf(stderr, "Error: RVA export directory inválido\n");
        return;
    }

    uint8_t *export_directory = base_address + rva_export_directory;

    // Leer nombre de la DLL
    uint32_t rva_name = *(uint32_t *)(export_directory + OFFSET_EXPORT_NAME);
    char *dll_name = (char *)(base_address + rva_name);
    printf("DLL Name: %s\n", dll_name);

    // Leer número de funciones exportadas
    uint32_t number_of_functions = *(uint32_t *)(export_directory + OFFSET_NUMBER_OF_FUNCTIONS);
    printf("Number of functions: %u\n", number_of_functions);

    // Leer ADDRESS_OF_NAMES
    uint32_t rva_address_of_names = *(uint32_t *)(export_directory + OFFSET_ADDRESS_OF_NAMES);
    if (!rva_address_of_names) {
        fprintf(stderr, "Error: RVA address of names inválido\n");
        return;
    }

    DWORD *address_of_names = (DWORD *)(base_address + rva_address_of_names);

    printf("Exported functions:\n");
    for (size_t i = 0; i < number_of_functions; i++) {
        DWORD name_rva = address_of_names[i];
        if (!name_rva) continue;

        char *function_name = (char *)(base_address + name_rva);
        DWORD y = create_hash(function_name);
        printf("try [%zu] %s\n", i, function_name);
        if (x == y){
            printf("[%zu] %s\n", i, function_name);
            return;
        }
    }
}

int main(void) {
    // Cargar kernel32.dll
    HMODULE module_handle = LoadLibraryA("ws2_32.dll");
    // module_handle = LoadLibraryA("kernel32.dll");

    if (!module_handle) {
        fprintf(stderr, "Error: no se pudo cargar kernel32.dll\n");
        return 1;
    }

    printf("Module handle: %p\n", (void *)module_handle);

    //     dd 0xaff835ad   ; WSACleanup:
    // dd 0x8b9d756a   ; WSASocket:
    // dd 0xed9ef56d   ; WSAStartup:
    // dd 0x939d7d9c   ; closesocket:
    // dd 0xedd8fe8a   ; connect:

    char* s = "WSACleanup";
    DWORD x = create_hash(s);

    // Ejecutar listado de exports
    print_exports((uint8_t *)module_handle, x);

    FreeLibrary(module_handle);
    
    printf("=== END ===");
    getchar();
    return 0;
}
