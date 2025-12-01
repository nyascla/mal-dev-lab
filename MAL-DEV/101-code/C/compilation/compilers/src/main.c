#include <stdio.h>
#include "suma.h"


__declspec(dllimport) void dll_func();

typedef int (*suma_func)(int,int);


int main() {

    printf("[+] Main \n");

    int resultado = suma(5, 3);
    printf("Resultado: %d\n", resultado);

    dll_func();
    
    return 0;
}