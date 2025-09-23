#include <windows.h>
#include <stdio.h>

/* Nueva función que imprime un mensaje */
__declspec(dllexport) void ReflectiveLoader() {
    printf("(DLL) ReflectiveLoader");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        printf("(DLL) Process Attached");
        // MessageBoxA(NULL, "(DLL) Process Attached", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_PROCESS_DETACH:
        printf("(DLL) Process Detached");
        // MessageBoxA(NULL, "(DLL) Process Detached!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_ATTACH:
        printf("(DLL) Thread Created");
        // MessageBoxA(NULL, "(DLL) Thread Created", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_DETACH:
        printf("(DLL) Thread Terminated");
        // MessageBoxA(NULL, "(DLL) Thread Terminated", "WARNING", MB_ICONEXCLAMATION);
        break;
    }
    return TRUE;
}