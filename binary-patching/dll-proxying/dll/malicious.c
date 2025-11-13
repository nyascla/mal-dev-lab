#include <windows.h>
#include <stdio.h>

HINSTANCE hOriginal = NULL;

void LoadOriginal() {
    
    hOriginal = LoadLibraryA("real.dll"); // tiene que estar en una de las direcciones `echo %PATH%`
    
    if (hOriginal == NULL) {
        printf("Error loading original DLL \n");
    }
}


// Función hook que será exportada
__declspec(dllexport) void WINAPI FuncA() {
    printf("[DLL hijacked] FuncA_Hook ejecutada\n");

    LoadOriginal();
    
    // Llama a la función original
    typedef void (WINAPI* pFuncA)();    // Prototipo de la función original
    pFuncA orig = (pFuncA)GetProcAddress(hOriginal, "FuncA");
    
    if (orig != NULL) {
        printf("[DLL hijacked] Llamando a FuncA original...\n");
        orig();  // Llama a la función original
    } else {
        printf("[DLL hijacked] Error: No se pudo encontrar FuncA original\n");
    }
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
        printf("[DLL hijacked] Process Attached\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("[DLL hijacked] Process Detached\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("[DLL hijacked] Thread Created\n");
        break;
    case DLL_THREAD_DETACH:
        printf("[DLL hijacked] Thread Terminated\n");
        break;
    }

    return TRUE;
}