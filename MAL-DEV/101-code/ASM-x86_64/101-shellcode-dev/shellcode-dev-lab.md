# Dev Lab

## NASM

Instalacion:

- `windows`: siguiente > siguiente
- `linux`: sudo apt install nasm

binario crudo, solo los opcodes:

``` bash
nasm -f bin main.asm -o shell_x86.bin
```

Objeto COFF de 64 bits:

``` bash
nasm -f win64 archivo.asm -o archivo.obj
```

## SCLAUNCHER

``` bash
sclauncher.exe -f=".\main.bin" -pe -o="main.exe"
```


## MAKE or NMAKE

> NOTA: NMAKE necesita Visual Studio 2022 Build tools

## Linking







