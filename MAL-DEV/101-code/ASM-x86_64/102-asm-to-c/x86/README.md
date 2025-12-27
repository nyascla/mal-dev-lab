nasm -f elf32 funcion.asm -o funcion.o

clang -m32 main.c funcion.o -o programa

---

nota: las biblioteas para compilar c en x86

notar como al linker le da igual si el .o viene de un .c o de un .asm