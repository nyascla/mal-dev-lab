#include <windows.h>

// 1. Exportamos la función
__declspec(dllexport) void HolaDLL() {
    MessageBoxA(
        NULL,
        "¡Función ejecutada desde la DLL!",
        "Mi DLL",
        MB_OK | MB_ICONEXCLAMATION
    );
}

// 2. Punto de entrada de la DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // Este código se ejecuta cuando la DLL se carga en un proceso.
            MessageBoxA(NULL, "DLL cargada en memoria.", "Mi DLL", MB_OK | MB_ICONINFORMATION);
            break;
        // Puedes manejar otros casos como DLL_PROCESS_DETACH si necesitas limpieza.
    }
    return TRUE; 
}