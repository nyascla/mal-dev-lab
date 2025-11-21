#include <windows.h>
#include <stdio.h>

int main() {
    // Cargar la DLL directamente
    HMODULE hDll = LoadLibraryA("sliver.dll");
    
    if (hDll == NULL) {
        printf("Error cargando la DLL: %d\n", GetLastError());
        return 1;
    }
    
    printf("DLL cargada exitosamente en: 0x%p\n", hDll);
    
    // Opcional: llamar a una función específica si es necesario
    // FARPROC function = GetProcAddress(hDll, "FunctionName");
    // if (function) function();
    
    // Mantener la DLL cargada
    printf("DLL cargada. Presiona Enter para descargar...\n");
    getchar();
    
    FreeLibrary(hDll);
    return 0;
}