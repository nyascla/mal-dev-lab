> ??? *PORQUE SALEN MUCHOS (DLL) Thread Created!*

## Link en tiempo de compilación
La DLL se carga una sola vez al inicio y se descarga al cerrar el EXE.
```
cl /LD my_dll.c user32.lib
cl compilation.c my_dll.lib user32.lib
```

## Link en tiempo de ejecucion
Windows incrementa el reference count de esa DLL. 
> Cuando el contador llega a 0, Windows descarga la DLL de memoria fisica.
Para no dejar memoria ocupada ni mantener DLLs cargadas innecesariamente, debes liberar la DLL explícitamente
```
cl /LD my_dll.c user32.lib
cl runtime.c user32.lib
```

## Notes

- ``.dll`` Implementación real de la librería (código ejecutable)
- ``.lib`` Import library: información de enlace (qué funciones están en la DLL y dónde encontrarlas)

## Como Windows carga una DLL

1. (LdrLoadDll en ntdll.dll) El Loader de Windows busca la DLL
    - Search Order:
    - importante para hijacking
        1. El directorio del ejecutable
        2. El directorio actual
        3. Directorios del PATH
        4. Directorios de sistema (System32, SysWOW64).
        - Si la DLL no se encuentra - LoadLibrary falla con NULL.
2. (NtMapViewOfSectio) Mapear el archivo PE en el espacio de direcciones virtual del proceso.\
    - Se crean páginas de memoria virtual para cada sección de la DLL (code, data, rdata, etc.) según el header PE
    > Aqui puede que la dll aun no este en memoria fisica "demand paging" solo se cargara en memoria si es necesario
3. Relocation
    - Cada DLL PE tiene un preferred base address
    - Si la DLL no puede cargarse en esa dirección (conflicto con otra DLL o EXE), Windows debe reubicarla (.reloc)
    - ASLR ??
4. Tablas de import/export
    - Export Table
        - (funciones y variables) que la DLL pone a disposición de otros módulos.
        - El loader construye la IAT
    - Import Table
        - Cada EXE o DLL tiene una tabla de importación (IAT – Import Address Table).
            1. El loader busca la DLL importada.
            2. Resuelve cada función de la import table.
            3. Reemplaza los punteros de la IAT con la dirección virtual de la función en memoria.
5. Windows implementa Copy-On-Write (COW) para páginas de DLL
    - (.text, .rdata) compartidas entre procesos, solo se cargan una vez en memoria física.
    - (.data) cada proceso recibe una copia privada, porque las variables globales son independientes.