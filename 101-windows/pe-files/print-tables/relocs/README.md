# Relocations (.reloc)

https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#the-reloc-section-image-only

- The .reloc Section (Image Only)
    - Base Relocation Block
    - Base Relocation Types

La sección .reloc es un "mapa de parches" que el compilador deja para el 
Cargador de Windows. Es una lista de todas las ubicaciones en el código que 
usan una dirección absoluta y que necesitan ser "arregladas" en tiempo de carga.

El cargador usa esta tabla para aplicar un "Delta" a cada dirección rota. 
Delta = ImageBaseReal (aleatoria) - ImageBasePreferida (del PE)

## Estructura de la Tabla `.reloc`

El DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC] apunta al inicio de esta lista.

La tabla de relocaciones no es una tabla simple, es una lista de bloques. 
Cada bloque representa una página de memoria (4KB) que contiene una o más 
direcciones que necesitan ser parcheadas.

El último bloque de la lista se identifica porque su SizeOfBlock es 0.

## 1. El Encabezado del Bloque

Cada bloque comienza con esta estructura de 8 bytes:

``` c
typedef struct _IMAGE_BASE_RELOCATION {
    DWORD   VirtualAddress;
    DWORD   SizeOfBlock;
} IMAGE_BASE_RELOCATION;
```

- `VirtualAddress`: La RVA (dirección relativa) de la página de 4KB a la que se refieren todos los parches de este bloque.
- `SizeOfBlock`: El tamaño total de este bloque en bytes (es decir, estos 8 bytes del encabezado + el tamaño de todas las entradas de parche que le siguen).

## 2. Las Entradas de Relocación (TypeOffset)

Inmediatamente después del encabezado, comienza un array de WORDs (valores de 16 bits). Cada WORD es una entrada de parche empaquetada.

- `4 bits (Type)`: Los 4 bits superiores. Indican el tipo de parche (ej. IMAGE_REL_BASED_DIR64 para un puntero de 64 bits)
    - IMAGE_REL_BASED_DIR64: para punteros de 64 bits
    - IMAGE_REL_BASED_HIGHLOW: para punteros de 32 bits
- `12 bits (Offset)`: Los 12 bits inferiores.

> Por qué solo 12 bits de Offset

Esta es la parte eficiente del diseño. El campo VirtualAddress del encabezado ya nos sitúa en la página de 4KB correcta.

- Una página de memoria tiene 4KB (4096 bytes).
- Para direccionar cualquier byte dentro de esa página (desde la posición 0 hasta la 4095), solo se necesitan 12 bits de datos.
- 2^12 = 4096.

Por lo tanto, el Offset de 12 bits es el desplazamiento (desde 0 a 4095) que se debe sumar a la VirtualAddress del bloque para encontrar la dirección exacta que necesita ser parcheada.

``` c
Dirección a Parchear = ImageBase + bloque.VirtualAddress + entrada.Offset
```
``` c
valorCorregido = Dirección a Parchear + Delta
```

## Ejemplo

``` c
// 1. Una variable global. El compilador la pone en la sección .data
int mi_variable_global = 100;

// 2. ¡EL PROBLEMA!
//    Un puntero global que almacena la dirección de la variable.
//    El compilador DEBE escribir una dirección de memoria fija aquí.
int* puntero_a_global = &mi_variable_global;
```

### Paso 1: El Compilador (Crea el Problema)

1. Asumamos que el compilador decide que la `ImageBase` preferida es `0x400000`.
1. Coloca mi_variable_global en la RVA `0x2000`. Su dirección "ideal" es `0x402000`.
1. Coloca `puntero_a_global` en la RVA `0x2008`.
1. El compilador escribe el valor `0x00402000` (la dirección "ideal") en el offset del archivo que corresponde a puntero_a_global.
1. Crea una entrada en `.reloc` que dice: "La dirección en la RVA `0x2008` es un puntero de 64 bits (`IMAGE_REL_BASED_DIR64`) y necesita ser parcheado si la `ImageBase` cambia".

### Paso 2: El Cargador (Calcula el Delta)

1. El Cargador de Windows (o tu loader) decide no cargar el PE en `0x400000` (por ASLR).
1. Elige una `ImageBase` aleatoria, por ejemplo: `0x7FF6B0000000`.
1. Calcula el "Delta":
    - Delta = ImageBaseReal - ImageBasePreferida
    - Delta = 0x7FF6B0000000 - 0x400000

### Paso 3: El Parcheo (Aplica el Delta)

1. El loader itera por la tabla .reloc
1. Encuentra la entrada creada en el Paso 1
1. El loader encuentra la dirección a parchear
1. El loader aplica el parche `valorCorregido = valorRoto + Delta`
