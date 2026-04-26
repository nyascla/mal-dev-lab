#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define OFFSET_TEB_NT_TIB           0x00
#define OFFSET_TEB_STACK_BASE      0x08
#define OFFSET_TEB_STACK_LIMIT     0x10
#define OFFSET_TEB_CLIENT_ID       0x40
#define OFFSET_TEB_LAST_ERROR      0x68
#define OFFSET_TEB_PEB             0x60
#define OFFSET_CLIENT_ID_PID       0x00
#define OFFSET_CLIENT_ID_TID       0x08


static inline uintptr_t GetCurrentTeb(void) {
    return __readgsqword(0x30); // GS:[0x30] → TEB
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

static void ShowTebInfo(void)
{
    uintptr_t teb = GetCurrentTeb();

    if (!teb) {
        fprintf(stderr, "[ERROR] No se pudo obtener el TEB\n");
        return;
    }

    printf("\n=== INFORMACION DEL TEB ===\n");
    printf("0x%p - TEB Address\n", (void*)teb);

    uintptr_t stackBase  = ReadPointer(teb + OFFSET_TEB_STACK_BASE);
    uintptr_t stackLimit = ReadPointer(teb + OFFSET_TEB_STACK_LIMIT);

    printf("0x%p - StackBase\n",  (void*)stackBase);
    printf("0x%p - StackLimit\n", (void*)stackLimit);

    uintptr_t peb = ReadPointer(teb + OFFSET_TEB_PEB);
    printf("0x%p - PEB (desde TEB)\n", (void*)peb);

    DWORD lastError = ReadDword(teb + OFFSET_TEB_LAST_ERROR);
    printf("LastErrorValue: %lu\n", lastError);

    uintptr_t clientId = teb + OFFSET_TEB_CLIENT_ID;

    DWORD pid = (DWORD)(uintptr_t)ReadPointer(clientId + OFFSET_CLIENT_ID_PID);
    DWORD tid = (DWORD)(uintptr_t)ReadPointer(clientId + OFFSET_CLIENT_ID_TID);

    printf("ProcessId: %lu\n", pid);
    printf("ThreadId : %lu\n", tid);
}



int main(void) {
    printf("; ============================================================\n");
    printf(";       LISTA TEB (x64)\n");
    printf("; ============================================================\n");

    ShowTebInfo();

    return 0;
}
