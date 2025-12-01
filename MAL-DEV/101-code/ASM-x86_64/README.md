# Shellcode (.bin)

Notas programacion shellcodes: [101-shellcode](./101-shellcode/)

## Shellcode VS Object files VS PE Files 

- `shellcode`: Código máquina puro, listo para ser inyectado y ejecutado directamente en memoria.
- `object-files`: Archivos intermedios (PE parcialmente construido) que contienen secciones y símbolos, pero aún no son ejecutables.
- `pe-files`: Ejecutables completos del formato Portable Executable, listos para ser cargados y ejecutados por el sistema operativo.

## Build

Requisitos: [shellcode-dev-lab](./101-shellcode/shellcode-dev-lab.md) 

### Messagebox

``` bash
make messagebox
```

### Reverse shell

``` bash
make reverse
```