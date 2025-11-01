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

// ------------------------------------------------------------
// Utilidad: leer un valor DWORD desde una dirección base
static uint32_t read_dword(const uint8_t *base, uintptr_t offset)
{
    return *(const uint32_t *)(base + offset);
}

// ------------------------------------------------------------
//
static size_t get_reloc_addr(unsigned char *base_address)
{
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)base_address;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) {
        fprintf(stderr, "[!] Error: Invalid DOS signature (MZ).\n");
        return 0;
    }

    const IMAGE_NT_HEADERS64 *nt = (const IMAGE_NT_HEADERS64 *)(base_address + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) {
        fprintf(stderr, "[!] Error: Invalid PE signature.\n");
        return 0;
    }

    const IMAGE_OPTIONAL_HEADER64 *opt64 = &nt->OptionalHeader;

    const DWORD rva_to_reloc = opt64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
    
    return base_address + rva_to_reloc;
}

// ------------------------------------------------------------
// Imprime información de exports de un módulo
static void print_relocs(size_t base_address)
{
    printf("=== RELOCATION TABLE (.reloc) ===\n");

    IMAGE_BASE_RELOCATION *reloc_block = (IMAGE_BASE_RELOCATION *)base_address;

    // La tabla de relocaciones es una serie de bloques. Iteramos hasta encontrar un bloque de tamaño 0.
    while (reloc_block->VirtualAddress != 0)
    {
        printf("  Block RVA: 0x%08X, Size: 0x%08X (%u)\n", reloc_block->VirtualAddress, reloc_block->SizeOfBlock, reloc_block->SizeOfBlock);

        // Calculamos el número de entradas de relocación en este bloque.
        DWORD entryCount = (reloc_block->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);

        // Las entradas de relocación (WORDs) empiezan justo después de la cabecera del bloque.
        WORD *pEntry = (WORD *)((unsigned char *)reloc_block + sizeof(IMAGE_BASE_RELOCATION));

        for (DWORD i = 0; i < entryCount; i++)
        {
            // Los 4 bits superiores son el tipo, los 12 inferiores son el offset.
            WORD type = (pEntry[i] >> 12);
            WORD offset = (pEntry[i] & 0x0FFF);

            if (type != IMAGE_REL_BASED_ABSOLUTE)
            { // Omitimos las entradas de relleno.
                printf("    - Type: %-2u, Offset: 0x%03X (Target RVA: 0x%08X)\n", type, offset, reloc_block->VirtualAddress + offset);
            }
        }

        // Pasamos al siguiente bloque.
        reloc_block = (IMAGE_BASE_RELOCATION *)((unsigned char *)reloc_block + reloc_block->SizeOfBlock);
    }
    printf("\n");
}

// ------------------------------------------------------------
int main(void)
{
    printf("; ============================================================\n");
    printf(";   x64 TABLA DE RELOCACIONES \n");
    printf("; ============================================================\n");

    const char *ws2_32 = "ws2_32.dll";
    const char *kernel32 = "kernel32.dll";

    HMODULE module_handle = LoadLibraryA(kernel32);

    if (!module_handle)
    {
        fprintf(stderr, "[!] Error: no se pudo cargar %s\n", kernel32);
        return 1;
    }

    printf("Module handle: %p\n", (void *)module_handle);

    unsigned char *buffer = (unsigned char*)module_handle;

    size_t x = get_reloc_addr(buffer);

    printf("Module handle suma: %p\n", (void *)x);

    print_relocs(x);

    FreeLibrary(module_handle);
    return 0;
}
