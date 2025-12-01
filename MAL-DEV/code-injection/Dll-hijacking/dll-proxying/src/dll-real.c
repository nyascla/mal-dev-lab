#include <windows.h>
#include <stdio.h>

__declspec(dllexport) void FuncA()
{
    printf("[DLL real] func FuncA\n");
}

__declspec(dllexport) void FuncB()
{
    printf("[DLL real] func FuncB\n");
}

__declspec(dllexport) void FuncC()
{
    printf("[DLL real] func FuncC\n");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
        printf("[DLL real] Process Attached\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("[DLL real] Process Detached\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("[DLL real] Thread Created\n");
        break;
    case DLL_THREAD_DETACH:
        printf("[DLL real] Thread Terminated\n");
        break;
    }

    return TRUE;
}