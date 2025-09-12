// mylib.c
#include <windows.h>
#include <stdio.h>

// Función 1
__declspec(dllexport) void HelloFromDLL()
{
    printf("Hola! Soy una funcion exportada desde la DLL.\n");
}

// Función 2
__declspec(dllexport) void AddNumbers(int a, int b)
{
    printf("La suma de %d + %d = %d\n", a, b, a + b);
}

// Función 3
__declspec(dllexport) void PrintMessage(const char* msg)
{
    printf("Mensaje recibido: %s\n", msg);
}

// Función 4
__declspec(dllexport) int MultiplyNumbers(int a, int b)
{
    int result = a * b;
    printf("La multiplicacion de %d * %d = %d\n", a, b, result);
    return result;
}

// DllMain es el punto de entrada de la DLL
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Se ejecuta cuando la DLL se carga en un proceso
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
