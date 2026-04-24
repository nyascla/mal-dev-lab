#include <stdio.h>

// Declaración de la función externa en ASM
extern int suma_y_multiplica(int a, int b);

int main() {
    int resultado = suma_y_multiplica(5, 3);
    printf("Resultado: %d\n", resultado);  // Debería imprimir 16 ( (5+3)*2 )
    return 0;
}