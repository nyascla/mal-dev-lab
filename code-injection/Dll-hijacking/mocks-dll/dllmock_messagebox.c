#include <windows.h>

__declspec(dllexport) void func()
{
    MessageBoxA(NULL, "(DLL) func", "func", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "(DLL) Process Attached", "DLL Event", MB_OK);
        break;

    case DLL_PROCESS_DETACH:
        MessageBoxA(NULL, "(DLL) Process Detached", "DLL Event", MB_OK);
        break;

    case DLL_THREAD_ATTACH:
        MessageBoxA(NULL, "(DLL) Thread Created", "DLL Event", MB_OK);
        break;

    case DLL_THREAD_DETACH:
        MessageBoxA(NULL, "(DLL) Thread Terminated", "DLL Event", MB_OK);
        break;
    }

    return TRUE;
}
