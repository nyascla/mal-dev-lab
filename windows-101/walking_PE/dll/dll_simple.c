// dll_simple.c
#include <windows.h>
#include <stdio.h>

__declspec(dllexport) void ReflectiveLoader(void) {
    printf("(function) ReflectiveLoader\n");
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
