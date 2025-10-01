// #include "pch.h"
#include <windows.h>
#include <stdio.h>

/* Nueva función que imprime un mensaje */
__declspec(dllexport) void hello_from_dll() {
    MessageBoxA(NULL, "__hello_from_dll__", "WARNING", MB_ICONEXCLAMATION);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "(DLL) Process Attached", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_PROCESS_DETACH:
        MessageBoxA(NULL, "(DLL) Process Detached!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_ATTACH:
        MessageBoxA(NULL, "(DLL) Thread Created!", "WARNING", MB_ICONEXCLAMATION);
        break;
    case DLL_THREAD_DETACH:
        MessageBoxA(NULL, "(DLL) Thread Terminated!", "WARNING", MB_ICONEXCLAMATION);
        break;
    }
    return TRUE;
}