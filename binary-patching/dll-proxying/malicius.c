#include <windows.h>
#include <stdio.h>

HINSTANCE hOriginal = NULL;

// Carga la DLL real
void LoadOriginal() {
    hOriginal = LoadLibraryA(".\\original.dll");
    
    if (hOriginal == NULL) {
        printf("Error loading original DLL \n");
    }
}

// Prototipo de la función original
typedef void (WINAPI* pFuncA)();

// Función hook que será exportada
__declspec(dllexport) void WINAPI FuncA() {
    printf("(DLL maliciosa) FuncA_Hook ejecutada\n");
    
    // Llama a la función original
    pFuncA orig = (pFuncA)GetProcAddress(hOriginal, "FuncA");
    
    if (orig != NULL) {
        printf("Llamando a FuncA original...\n");
        orig();  // Llama a la función original
    } else {
        printf("Error: No se pudo encontrar FuncA original\n");
    }
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
        printf("(DLL malicius) Process Attached\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("(DLL malicius) Process Detached\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("(DLL malicius) Thread Created\n");
        break;
    case DLL_THREAD_DETACH:
        printf("(DLL malicius) Thread Terminated\n");
        break;
    }

    return TRUE;
}