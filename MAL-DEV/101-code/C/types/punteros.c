#include <stdint.h> // Para Enternos
#include <stddef.h> // Para size_t
#include <inttypes.h> // <-- La biblioteca de formatos

int main() {

    // ------------------------------------------------------------
    // --- ARITMÉTICA DE PUNTEROS ---
    size_t mi_array[] = {100, 200, 300, 400};
    
    size_t* ptr = &mi_array[0];
    uintptr_t addr = (uintptr_t)ptr; // Convertir a entero para ver la dirección


    ptr = ptr + 1;      // Suma 1 * sizeof(size_t)
    addr = addr + 1;    // Suma 1 byte

    // ------------------------------------------------------------
    // --- CONST ---
    const int* ptr;         // No se puede modificar el valor apuntado
    int* const ptr;         // No se puede modificar la dirección del puntero
    const int* const ptr;   // No se puede modificar ni el valor ni la dirección

    return 0;

}