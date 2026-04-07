#include <stdio.h>
#include <stdint.h>

#define ROTATE_BITS 7


// Rotación a la izquierda de un entero de 32 bits
static inline uint32_t rol(uint32_t val, unsigned int r_bits, unsigned int max_bits) {
    r_bits %= max_bits;
    return (val << r_bits) | (val >> (max_bits - r_bits));
}

// Crear hash consistente con export_name
uint32_t create_hash(const char *export_name) {
    uint32_t result = 0;
    for (const char *ptr = export_name; *ptr; ptr++) {
        result = rol(result, ROTATE_BITS, 32) ^ (uint32_t)tolower((unsigned char)*ptr);
    }
    return result;
}