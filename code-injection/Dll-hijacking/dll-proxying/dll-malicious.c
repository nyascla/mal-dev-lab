#include <windows.h>
#include <stdio.h>


__declspec(dllexport) void WINAPI FuncA() {
    printf("[DLL hijacked] FuncA_Hook ejecutada\n");

    // Nuestra Dll maliciosa exporta:
    // 
    //      Export Address Table -- Ordinal Base 1
    //          [   0] +base[   1] 1437 Export RVA
    //          [   1] +base[   2] d05a Forwarder RVA -- og_real.FuncB
    //          [   2] +base[   3] d06e Forwarder RVA -- og_real.FuncC
    // 
    // El loader detecta estos exports como una dependecia con "og_real.dll" y carga la dll en memoria

    HINSTANCE hOriginal = LoadLibraryA("real-old.dll");      // Solo recuperamos el handle la dll ya esta en memoria
    typedef void (WINAPI* pFuncA)();                        // Prototipo de la función original
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