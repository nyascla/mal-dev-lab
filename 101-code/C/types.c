#include <stdint.h> // Para Enternos
#include <stddef.h> // Para size_t
#include <inttypes.h> // <-- La biblioteca de formatos

int main() {

    // ------------------------------------------------------------
    // --- PORTABILIDAD ENTEROS ---
    uint8_t my_byte = 0xFF;         // 8 bits sin signo
    int8_t my_signed_byte = -1;     // 8 bits con signo
    size_t my_size = 5000000000;    // Tipo para tamaños (depende de la plataforma)

    uint64_t mi_numero_grande = 12345678901234567890ULL;
    int32_t mi_numero_32 = -2000;
    printf("64-bit (decimal): %" PRIu64 "\n", mi_numero_grande);
    printf("64-bit (hex):     0x%" PRIX64 "\n", mi_numero_grande);
    printf("32-bit (decimal): %" PRId32 "\n", mi_numero_32);
    // Para ver el patrón de bits de un negativo en hex,
    // hacemos un cast a su tipo 'unsigned' equivalente.
    printf("32-bit (hex):     0x%" PRIX32 "\n", (uint32_t)mi_numero_32);

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

    
}