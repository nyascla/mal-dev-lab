#include <stdio.h>

extern int asm_add(int a, int b);   // C verá asm_add, linker busca _asm_add

int main(void) {
    printf("%d\n", asm_add(2, 3));
    return 0;
}
