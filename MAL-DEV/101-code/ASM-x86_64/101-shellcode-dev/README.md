# Shellcode

## 1. Position-Independent Code (PIC)

* El shellcode debe ejecutarse desde **cualquier dirección de memoria**.
* No puede asumir una base fija ni offsets estáticos.
* Necesita conocer su posición en tiempo de ejecución.
* Técnica clásica (x86): call-pop
    * Permite acceso relativo a datos, cadenas y estructuras internas.
  ```asm
  call geteip
  geteip:
      pop edx
      lea edx, [edx - 5]
  ```

## 2. Runtime Linking en Shellcode

### Objetivo

* Resolver funciones de DLLs (ej. *kernel32.dll*) sin loader ni linker.

### Pasos

1. Acceder al **PEB**:

   * x86: `FS:[0x30]`
   * x64: `GS:[0x60]`
2. Recorrer `InMemoryOrderModuleList` → obtener **module base addresses**.
3. Parsear encabezado **PE** del módulo.
4. Localizar la **Export Table**.
5. Resolver función:

   * `func_addr = module_base + RVA`.

### Hashing de nombres

* Evita cadenas en claro (evasion / anti‑análisis).
* Solo se almacena un **hash** de cada API.
* Se recorre la tabla de exportaciones, se hashea cada nombre, se compara.


## 3. ABI en x86 y x64

> NOTA Cuidar:
>   * Preservación de registros no volátiles.
>   * [stack-frame](./stack-frame.md)
>   * [registros](./registers.md)

### [x86-calling-convention](./x86-calling-convention.md)

* Argumentos por **pila**, orden **right-to-left**.

### [x64-calling-convention](./x64-calling-convention.md)

* Primeros 4 parámetros en: **RCX, RDX, R8, R9**, Resto → pila.
* Alineación obligatoria**: `RSP % 16 = 0` antes de una call.
* Requiere 32 bytes de shadow space.

## Compilar `.c` con el mínimo nivel de optimización

``` bash
clang -S -O0 -fno-asynchronous-unwind-tables -fno-exceptions main.c -o main.s
```