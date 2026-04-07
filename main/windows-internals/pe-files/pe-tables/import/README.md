# La Estructura de Importaciones (Sección .idata)

![alt text](./img/image.png)

La Tabla de Direcciones de Importación (IAT) es la "libreta de direcciones" de 
un ejecutable. Es una tabla en la memoria que el Cargador de Windows rellena con 
las direcciones reales de las funciones (como printf o Sleep) que el programa necesita.

Esta "libreta" se construye usando la información almacenada en la sección .idata del archivo en disco.

## 1. El Punto de Partida: El Puntero del Header

El Cargador de Windows no sabe dónde está la sección .idata por su nombre. 
En su lugar, mira en el OptionalHeader del PE y busca la entrada del directorio de datos:

DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]

## 2. La Estructura de .idata: Una Base de Datos

La sección .idata no es una tabla simple, es una "base de datos" de tres niveles que se apuntan entre sí.

### Nivel 1: El Array de DLLs (IMAGE_IMPORT_DESCRIPTOR)

La RVA del DataDirectory apunta a un array de IMAGE_IMPORT_DESCRIPTOR. Hay una 
estructura de estas por cada DLL que el programa importa (una para user32.dll, 
otra para kernel32.dll, etc.).

El array termina con una estructura llena de ceros.

Cada `IMAGE_IMPORT_DESCRIPTOR` es un "índice" que contiene dos punteros (RVAs) cruciales:
- `Name`: RVA que apunta a un string con el nombre de la DLL (ej. "user32.dll").
- `OriginalFirstThunk` (OFT): RVA que apunta a la "Lista de Nombres".
- `FirstThunk` (FT): RVA que apunta a la "Lista de Direcciones" (la IAT real).

### Nivel 2: Los Arrays Paralelos (OFT y IAT)

- `OriginalFirstThunk (OFT)`: Los nombres de las funciones (Nivel 3).
    - Es un array de RVAs. Cada entrada apunta a un nombre de función (Nivel 3).
    - El cargador lo usa para saber qué funciones tiene que importar (ej. "MessageBoxA", "FindWindowA").
- `FirstThunk (IAT)`: Las direcciones de las funciones (Nivel 3).
    - Este es el array que se convertirá en la IAT.
    - En el archivo en disco, es una copia idéntica del OFT.
    - El cargador sobrescribe este array durante la carga.

### Nivel 3: Los Nombres de las Funciones (IMAGE_IMPORT_BY_NAME)

Cada entrada del OriginalFirstThunk (OFT) apunta a una pequeña estructura que contiene el nombre de la función:

``` c
typedef struct _IMAGE_IMPORT_BY_NAME {
    WORD Hint;      // Un "índice" opcional
    CHAR Name[1];   // El nombre de la función (ej. "MessageBoxA")
} IMAGE_IMPORT_BY_NAME
```

## Dumpbin

```
dumpbin /headers bin\main.exe > headers.txt
dumpbin /imports bin\main.exe > imports.txt
```