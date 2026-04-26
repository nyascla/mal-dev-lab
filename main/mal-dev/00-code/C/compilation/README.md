# From .c to .exe

`Compilador`: Traduce código fuente (C, C++, etc.) a código objeto (.obj o .o), que contiene instrucciones máquina parciales (aún sin unir). Su trabajo es convertir cada archivo fuente de manera independiente.

`Linker`: Une todos los archivos objeto y librerías necesarias en un ejecutable (.exe) o biblioteca (.dll).

> Compilation:
> - .c   (fuente)
> - .s   (ensamblador)
> - .o / .obj   (código objeto)

> Linking:
> - .exe   (ejecutable final)
> - .dll   (librería dinámica)
> - .lib   (puede ser estática o import library)


## 1. Preprocesamiento

`Qué hace`: El preprocesador (cpp) lee el código fuente y procesa las directivas de preprocesador, que son líneas que comienzan con #:

- #include <stdio.h> → reemplaza por el contenido de la cabecera.
- #define PI 3.14 → reemplaza todas las apariciones de PI.
- #ifdef, #ifndef, #if → incluyen/excluyen código condicionalmente.

`Salida`: Un archivo C “expandido”, listo para compilar, que incluye todas las cabeceras y macros resueltas.

```bash
clang -E main.c -o main.i
```

## 2. Compilación

`Qué hace`: Convierte el código preprocesado en código ensamblador para la arquitectura del sistema.

- Traduce instrucciones C a instrucciones de bajo nivel entendibles por la CPU (pero todavía no es binario ejecutable).

`Salida`: Archivo de ensamblador (.s) o directamente un objeto intermedio (.o).

```bash
clang -S main.i -o main.s  # Genera ensamblador
clang -c main.i -o main.o  # Genera objeto binario intermedio
```

## 3. Ensamblado (Assembly)

`Qué hace`: Convierte el código ensamblador en código máquina y lo guarda en un archivo objeto (.o o .obj).

- Contiene instrucciones binarios y información simbólica (funciones, variables globales).
- No es ejecutable aún, porque falta linkear librerías y otros objetos.

Salida: Objeto intermedio (.o). Estos ya tienen secciones como(.text .data .bss)

## 4. Linking (Enlazado)

`Qué hace`: El linker une:
- Todos los archivos .o necesarios
- Todas las Librerías necesarias
- Código de arranque (startup code: _start o mainCRTStartup en Windows)
- Genera cabecera del ejecutable

`Salida`: Archivo ejecutable (.exe, .out, etc.), listo para correr.

``` bash
# -lm → enlaza la librería matemática.
clang main.o suma.o -o main.exe -lm
clang main.o suma.o -o main.exe -lm -static
```

### Linking: (Archivos .o)

- Junta todas las .text en un bloque continuo en memoria.
- Junta todas las .data y .bss.

`Ejemplo`: main.o tenía una instrucción `call suma`. El linker reemplaza esa instrucción con un salto a la dirección real de suma, por ejemplo `call 0x1010`.

### Linking: (Librerías)

Nota: Un ejecutable C siempre necesita librerías del sistema.
- Linux: libc...
- Windows: msvcrt.dll...

#### Estático: 

Se incluyen todas las librerías en el .exe → tamaño mayor, independiente.

- `Ejemplo`: Todas las llamadas a printf en tu código se reemplazan por saltos a la dirección del código de printf ya dentro del .exe

### Dinámico:  

El linker no copia el código este se enlaza con DLLs o .so → más pequeño, dependiente de librerías externas.

`Ejemplo`: Crea una entrada en la tabla de importaciones (IAT) que el loader llenará con la dirección real de printf en tiempo de ejecución. En el código, la llamada a printf no apunta directamente al código, sino a la dirección que está en la IAT.

## 5. Ejecución

El loader del sistema operativo:

1. Carga el ejecutable en memoria.
1. Asigna direcciones a variables globales y funciones.
1. Llama a la función de inicio (_start), que a su vez llama a main().
1. Ejecuta tu programa.
