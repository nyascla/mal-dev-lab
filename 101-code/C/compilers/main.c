#include <windows.h>

// 1. IMPORTANTE: Declaramos la función que está en la DLL.
//    __declspec(dllimport) le dice al compilador:
//    "Esta función no está aquí, vive en una DLL externa".
__declspec(dllimport) void HolaDLL();

int main() {
    MessageBoxA(NULL, "EXE iniciado. Llamando a la DLL...", "Mi Programa EXE", MB_OK);

    // 2. Simplemente llamamos a la función.
    //    El sistema operativo se encarga de todo lo demás.
    HolaDLL();
    
    return 0;
}