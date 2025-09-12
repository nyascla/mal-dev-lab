// main.c
#include <windows.h>
#include <stdio.h>

// Declaramos la función como si ya existiera
__declspec(dllimport) void HelloFromDLL();

int main()
{
    printf("Llamando a la funcion dentro de la DLL...\n");
    HelloFromDLL();
    return 0;
}

// cl main.c mylib.lib /Fe:main.exe
