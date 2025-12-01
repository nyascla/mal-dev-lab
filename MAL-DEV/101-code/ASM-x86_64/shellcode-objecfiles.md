# Shellcode VS Object files VS PE Files 

Ambos son ficheros que contienen codigo maquina.

## Shellcode (.bin)

Es código máquina plano listo para ejecutarse, generalmente en memoria.

Contenido:
- Solo código puro (.text)

``` bash
nasm -f bin hello.asm -o hello.bin
```

## Object files (.o, .obj)

No son directamente ejecutables. Son archivos de objeto generados por el compilador o ensamblador. 

Contenido:
- Secciones de código (.text)
- Datos (.data, .bss)
- Información de símbolos y referencias externas

``` bash
nasm -f elf64 hello.asm -o hello.o
nasm -f win64 hello.asm -o hello.obj
```

## PE Files