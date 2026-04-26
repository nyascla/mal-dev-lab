# EXPORT TABLE

## Conseguir punto a _IMAGE_EXPORT_DIRECTORY

### 1. Navegar _IMAGE_DOS_HEADER

- Al cargar un ejecutables o DLL de Windows en memoria este se mapea a unas direciones viruales la primera direccion de ese mapping es el Base Address.
- En ese mismo Base Address se encuentra la struct _IMAGE_DOS_HEADER
- Dentro de esa struct en un offset de 0x3c encontramos e_lfanew
- Esta es una DWORD que contiene el offset a la struct _IMAGE_NT_HEADERS
- Base Address + e_lfanew = puntero a _IMAGE_NT_HEADERS

### 2. Navegar _IMAGE_NT_HEADERS

- En un offset de 0x18 nos encontramos un puntero a _IMAGE_OPTIONAL_HEADER
- Base Address + e_lfanew + 0x18 = puntero a _IMAGE_OPTIONAL_HEADER

### 3. Navegar _IMAGE_OPTIONAL_HEADER

> Esta struct no es igual en x86 y x64

- En un offset de (0x60 o 0x70) nos encontramos el puntero a _IMAGE_DATA_DIRECTORY DataDirectory[16]
- Esto es un Array donde habra 16 _IMAGE_DATA_DIRECTORY contiguos en memoria
- (4 bytes + 4 bytes) * 16 = 126 bytes
- cada _IMAGE_DATA_DIRECTORY es un puntero + tamaño para un recursos importantes del PE.

``` c
typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD VirtualAddress;  // RVA (offset en memoria cuando se carga)
    DWORD Size;            // Tamaño de la tabla o directorio
} 
```

- Para la Export table tenmos que consegur la primera posicion DataDirectory[0]
- Base Address + e_lfanew + 0x18 + (0x60 o 0x70) = RVA to _IMAGE_EXPORT_DIRECTORY
- Base Address + RVA to _IMAGE_EXPORT_DIRECTORY = puntero a _IMAGE_EXPORT_DIRECTORY


## Recorrer exports y recuperar punteros a las funciones

en la struct _IMAGE_EXPORT_DIRECTORY tenemos 3 listas importantes para resolver la direccion de las funciones exportadas

0x1c DWORD AddressOfFunctions;
0x20 DWORD AddressOfNames;          
0x24 DWORD AddressOfNameOrdinals;

Las 3 son RVA a arrays:

`AddressOfNames`: un array donde cada posicion es un RVA a una str con el nombre de una funcion.

`AddressOfNameOrdinals`: un array de Words (2 bytes), almacena los ordinals que sirven para encontrar los rva a las funciones en el array AddressOfFunctions.
    - AddressOfNames[i]
    - AddressOfFunctions[AddressOfNameOrdinals[i]]

`AddressOfFunctions`: almacena los rva a las funciones AddressOfFunctions[ordinal] = rva_function
