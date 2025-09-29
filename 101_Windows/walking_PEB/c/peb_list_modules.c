#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <stdint.h>

// Offsets para PEB y estructuras en x64
#define OFFSET_PEB_IMAGEBASE     0x10
#define OFFSET_PEB_BEINGDEBUGGED 0x02
#define OFFSET_PEB_LDR           0x18
#define OFFSET_LDR_INLOADORDER   0x10
#define OFFSET_LDR_ENTRY_DLLBASE 0x30
#define OFFSET_LDR_ENTRY_BASENAME 0x58
#define OFFSET_UNICODE_STRING_BUFFER 0x8

// Obtiene la dirección del PEB en x64
static inline uintptr_t GetCurrentPeb(void) {
    return __readgsqword(0x60); // GS:[0x60]
}

// Lee un puntero desde una dirección de memoria
static inline uintptr_t ReadPointer(uintptr_t address) {
    return *(uintptr_t*)address;
}

// Lee un DWORD desde una dirección de memoria
static inline DWORD ReadDword(uintptr_t address) {
    return *(DWORD*)address;
}

// Lee un BYTE desde una dirección de memoria
static inline BYTE ReadByte(uintptr_t address) {
    return *(BYTE*)address;
}

// Muestra información básica del PEB
static uintptr_t ShowPebInfo(void) {
    uintptr_t peb = GetCurrentPeb();
    if (!peb) {
        fprintf(stderr, "[ERROR] No se pudo obtener el PEB\n");
        return 0;
    }

    printf("=== INFORMACION DEL PEB ===\n");
    printf("PEB Address: 0x%p\n", (void*)peb);

    uintptr_t imageBase = ReadPointer(peb + OFFSET_PEB_IMAGEBASE);
    printf("ImageBaseAddress: 0x%p\n", (void*)imageBase);

    BYTE beingDebugged = ReadByte(peb + OFFSET_PEB_BEINGDEBUGGED);
    printf("BeingDebugged: %d\n", beingDebugged);

    uintptr_t ldr = ReadPointer(peb + OFFSET_PEB_LDR);
    printf("Ldr: 0x%p\n", (void*)ldr);

    return ldr;
}

// Lista los módulos cargados en memoria
static void ListLoadedModules(uintptr_t ldr) {
    if (!ldr) {
        fprintf(stderr, "[ERROR] LDR es NULL\n");
        return;
    }

    printf("\n=== MODULOS CARGADOS ===\n");

    uintptr_t listHead = ReadPointer(ldr + OFFSET_LDR_INLOADORDER);
    uintptr_t currentEntry = listHead;

    if (!currentEntry) {
        fprintf(stderr, "[ERROR] Lista de módulos vacía\n");
        return;
    }

    do {
        uintptr_t dllBase = ReadPointer(currentEntry + OFFSET_LDR_ENTRY_DLLBASE);
        uintptr_t baseDllNamePtr = ReadPointer(currentEntry + OFFSET_LDR_ENTRY_BASENAME + OFFSET_UNICODE_STRING_BUFFER);

        if (baseDllNamePtr) {
            wprintf(L"%s - 0x%p\n", (wchar_t*)baseDllNamePtr, (void*)dllBase);
        }

        currentEntry = ReadPointer(currentEntry);

    } while (currentEntry && currentEntry != listHead);
}

int main(void) {
    printf("LISTA MODULOS ITERANDO PEB (x64)\n");

    uintptr_t ldr = ShowPebInfo();
    ListLoadedModules(ldr);

    return 0;
}
