## fases de compilacion

.c
.s
.o
.dll
.exe
.lib

## compilacion vs linking

funciones static

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

## Link estatico
Al compilar main.exe el linker copia fisicamente el codigo de la dll dentro de main.exe


## Notes

- ``.dll`` Implementación real de la librería (código ejecutable)
- ``.lib`` Import library: información de enlace (qué funciones están en la DLL y dónde encontrarlas)
