#include <stdio.h>

// 1. Declaramos la función que vamos a importar desde la DLL.
//    __declspec(dllimport) le indica al compilador que la implementación
//    de 'hello' se encuentra en una DLL externa.
__declspec(dllimport) void hello();

// 2. Usamos la directiva #pragma para indicar al enlazador (linker)
//    que debe buscar y enlazar la biblioteca de importación 'dllmock.lib'.
//    Esto elimina la necesidad de especificarlo en la línea de comandos.
#pragma comment(lib, "../dll/bin/dllmock.lib")

int main() {
    printf("[MAIN] El programa ha comenzado. La DLL deberia cargarse automaticamente.\n");
    hello(); // 3. Llamamos a la función importada.
    printf("[MAIN] La funcion 'hello' de la DLL ha sido ejecutada.\n");
    return 0;
}