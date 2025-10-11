#include <windows.h>
#include <stdio.h>

__declspec(dllexport) void ReflectiveLoader() {
    printf("(DLL) func ReflectiveLoader");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        printf("(DLL) Process Attached");
        break;
    case DLL_PROCESS_DETACH:
        printf("(DLL) Process Detached");
        break;
    case DLL_THREAD_ATTACH:
        printf("(DLL) Thread Created");
        break;
    case DLL_THREAD_DETACH:
        printf("(DLL) Thread Terminated");
        break;
    }
    return TRUE;
}