# Linking DLLs

## DLL vinculada implícitamente (enlace estático a nivel de linker)

La DLL se carga una sola vez al inicio y se descarga al cerrar el EXE.

En el momento de la compilacion del main.c el compilador crea la esctructura .idata 
con la informacion que el loader tendra que

## DLL vinculada explícitamente (en tiempo de ejecución)

> Windows incrementa el reference count de esa DLL. Cuando el contador llega a 0, Windows descarga la DLL de memoria fisica.

# Compilación estática `.lib` (sin usar DLLs)

Al compilar main.exe el linker copia fisicamente el codigo de la dll dentro de main.exe

> ## Notes
> 
> - ``.dll`` Implementación real de la librería (código ejecutable)
> - ``.lib`` Import library: información de enlace (qué funciones están en la DLL y dónde encontrarlas)
> 