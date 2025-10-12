#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <stdint.h>

// Offsets para PEB y estructuras en x64
#define OFFSET_PEB_IMAGEBASE        0x10
#define OFFSET_PEB_BEINGDEBUGGED    0x02
#define OFFSET_PEB_LDR              0x18
#define OFFSET_LDR_INLOADORDER      0x10
#define OFFSET_LDR_ENTRY_DLLBASE    0x30
#define OFFSET_LDR_ENTRY_BASENAME   0x58
#define OFFSET_UNICODE_STRING_BUFFER 0x8

// Obtiene la dirección del PEB en x64
static inline uintptr_t GetCurrentPeb(void) {
    return __readgsqword(0x60); // GS:[0x60]
}

// Lee un puntero desde una dirección de memoria
static inline uintptr_t ReadPointer(uintptr_t address) {
    return *(uintptr_t*)address;
}

// ------------------------------------------------------------
// Lista los módulos cargados en memoria
void* GetKernell32() {
    uintptr_t peb = GetCurrentPeb();
    uintptr_t ldr = ReadPointer(peb + OFFSET_PEB_LDR);

    uintptr_t listHead = ReadPointer(ldr + OFFSET_LDR_INLOADORDER);
    uintptr_t currentEntry = listHead;

    if (!currentEntry) {
        fprintf(stderr, "[ERROR] Lista de módulos vacía\n");
        return;
    }

    do {
        uintptr_t dllBase = ReadPointer(currentEntry + OFFSET_LDR_ENTRY_DLLBASE);
        uintptr_t baseDllNamePtr = ReadPointer(currentEntry + OFFSET_LDR_ENTRY_BASENAME + OFFSET_UNICODE_STRING_BUFFER);

        if (baseDllNamePtr != NULL && wcscmp(baseDllNamePtr, L"KERNEL32.DLL") == 0) {
            return (void*)dllBase;
        }

        currentEntry = ReadPointer(currentEntry);

    } while (currentEntry && currentEntry != listHead);
}


void* rip() {
    return _ReturnAddress();
    // Devuelve la direccion de memoria siguiente al call rip()
}

__declspec(dllexport) void ReflectiveLoader() {
    printf("RIP actual (aprox, return address): %p\n", rip());
    printf("Kernell32 Base: %p\n", GetKernell32());
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        printf("(DllMain) Process Attached\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("(DllMain) Process Detached\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("(DllMain) Thread Created\n");
        break;
    case DLL_THREAD_DETACH:
        printf("(DllMain) Thread Terminated\n");
        break;
    }
    return TRUE;
}