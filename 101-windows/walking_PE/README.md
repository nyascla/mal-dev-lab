# Portable Executable (PE)

Un "image" es unarepresentación completa de un ejecutable (PE) cargado en memoria. 
Se llama así porque el loader de Windows mapea el archivo en disco en la 
memoria virtual del proceso como una imagen coherente del binario (cabeceras + secciones + datos).

- > Buscar offsets: [PE Format Layout](./utils/PE%20Format%20Layout.pdf)
- > Un vistazo general: [PE Format Walkthrough](./utils/PE%20Format%20Walkthrough.pdf)

``` bash
dumpbin /headers        bin\main.exe    > headers.txt
dumpbin /imports        bin\main.exe    > imports.txt
dumpbin /exports        bin\mylib.dll   > exports.txt
dumpbin /sections       bin\main.exe    > sections.txt
dumpbin /relocations    bin\main.exe    > relocations.txt
dumpbin /dependents     bin\main.exe    > dependents.txt
dumpbin /all            bin\main.exe    > all_info.txt
```

## (1.) IMAGE_DOS_HEADER (DOS header)
>  offset zero 

- (e_lfanew) offset a NT Headers.

## (2.) IMAGE_NT_HEADERS (NT headers)
> offset e_lfanew

- 0x00 DWORD Signature
- 0x04 Struct IMAGE_FILE_HEADER
    - Machine (32 o 64)
    - SizeOfOptionalHeader
    - NumberOfSections
- 0x18 Struct IMAGE_OPTIONAL_HEADER

## (3.) IMAGE_OPTIONAL_HEADER (Optional header 32/64)
> offset e_lfanew + 0x18

- ``0x10/0x10 DWORD`` AddressOfEntryPoint: RVA del primer byte que se ejecuta
- ``0x1c/0x18 DWORD/QWORD`` ImageBase: Dirección favorita para carga el PE
- ``0x60/0x70 IMAGE_DATA_DIRECTORY[16]`` Data Directory: Array de 16 posiciones en cada posicion hay un RVA a una estructura importante
    - ``0x00 IMAGE_DIRECTORY_ENTRY_EXPORT`` Struct para la info de los exports
    - ``0x08 IMAGE_DIRECTORY_ENTRY_IMPORT`` Struct para la info de los imports

## (4.) IMAGE_SECTION_HEADER (section headers)
> offset e_lfanew + 0x18 + SizeOfOptionalHeader

de IMAGE_FILE_HEADER sacamos NumberOfSections

para cada seccion hay un IMAGE_SECTION_HEADER

- 0x08 VirtualSize: Tamaño real en memoria
- 0x0c VirtualAddress: RVA en memoria
- 0x10 SizeOfRawData: Tamaño en disco
- 0x14 PointerToRawData: RVA en disco 
- 0x24 Characteristics: Permisos (R/W/X)

- ![alt text](./utils/image.png)

# Disco vs Memoria

## Disco
```
+---------------------+
| DOS Header          |
| NT Headers          |
| Section Headers     |
+---------------------+
| .text (código)      |
| .rdata (constantes) |
| .data (variables)   |
| .rsrc (recursos)    |
+---------------------+
```

## Memoria
```
BaseAddress (ImageBase)
│
├── Headers (mapeados al inicio)
│
├── .text  → RX (ejecutable)
├── .rdata → R
├── .data  → RW
├── .rsrc  → R
└── ... (otras secciones)
```

## General

EntryPoint:
- Memoria: ImageBase + AddressOfEntryPoint
- Disco: (AddressOfEntryPoint - VirtualAddress) + PointerToRawData

### Imports (IMAGE_DIRECTORY_ENTRY_IMPORT)

En disco el IAT es una tabla vacía de punteros que el loader rellenará

> Guia pasa a paso recorrer la import table en memoria [walking_import_table](../walking_export_table/README.md)

### Exports (IMAGE_DIRECTORY_ENTRY_EXPORT)

- Obtendremos en AddressOfFunctions el RVA a la funcion 
- ImageBase + RVA = offset to jmp relativo hacia la implementacion real en .text

> Guia pasa a paso recorrer la export table en memoria [walking_export_table](../walking_export_table/README.md)



