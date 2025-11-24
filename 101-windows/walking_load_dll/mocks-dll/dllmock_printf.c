#include <windows.h>
#include <stdio.h>

__declspec(dllexport) void func()
{
    printf("(DLL) func func\n");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
        printf("(DLL) Process Attached\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("(DLL) Process Detached\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("(DLL) Thread Created\n");
        break;
    case DLL_THREAD_DETACH:
        printf("(DLL) Thread Terminated\n");
        break;
    }

    return TRUE;
}