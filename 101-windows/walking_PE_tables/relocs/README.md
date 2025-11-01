# RELOCS

The .reloc Section (Image Only)
https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#the-reloc-section-image-only

## Base Relocation Block

el sistema agrupa los parches por páginas de memoria.la relocacioens se hacen a nivel de pagina 4KB (4096 bytes).

Para apuntar a cualquier byte dentro de esa página, solo necesitas un número entre 0 y 4095.

2^12 = 4096. Por lo tanto, 12 bits son la cantidad exacta de información necesaria para almacenar cualquier número entre 0 y 4095.

Each base relocation block starts with the following structure:

``` c
typedef struct _IMAGE_BASE_RELOCATION {
    DWORD   VirtualAddress;
    DWORD   SizeOfBlock;
} IMAGE_BASE_RELOCATION;
typedef IMAGE_BASE_RELOCATION UNALIGNED * PIMAGE_BASE_RELOCATION;
```

The Block Size field is then followed by any number of Type or Offset field entries. 

Each entry is a WORD (2 bytes) and has the following structure:

4 bits: Type
12 bits: Offset

``` c
// (PWORD) es un puntero a unsigned short (16 bits)
PWORD pEntry = (PWORD)(pBlock + 1);

// pEntry[i] es tu WORD (el valor de 16 bits)

// Desplaza los 12 bits de la derecha para quedarte solo con los 4 de la izquierda
DWORD type = (pEntry[i] >> 12);

// Aplica una máscara AND con 0x0FFF (que es 0000 1111 1111 1111)
// para quedarte solo con los 12 bits de la derecha
DWORD offset = (pEntry[i] & 0x0FFF);

```

Base Relocation Types
