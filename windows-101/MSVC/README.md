# MSVC

## Compilador [cl]

- ``/nologo``: no muestren el “banner” inicial con la versión del compilador/enlazador
- ``/W3``: en MSVC controla el nivel de advertencias (warnings) que el compilador muestra
- ``/MDd``: usar la versión debug de la CRT dinámica (en vez de /MD).
- ``/c``: Compila solo hasta generar el archivo objeto (.obj), pero no enlaces.
- ``/Zi``: generar información de depuración (PDB).
- ``/Od``: desactivar optimizaciones (mejora la depuración).
- ``/RTC1``: comprobaciones en tiempo de ejecución (desbordamientos de pila, uso de variables - no inicializadas) — útil en debug.
- ``/I include``: en cl le dice al compilador de MSVC que agregue un directorio al include search path, es decir, a la lista de rutas donde buscará los archivos de cabecera (#include "..." o #include <...>).

```
cl /nologo /W3 /MDd /Zi /Od /RTC1 /I include /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
```

## Linker [link]

- ``/DEBUG``: provoca que el linker cree un fichero .pdb (Program Database) y escriba en el PE (EXE/DLL) una entrada IMAGE_DEBUG_DIRECTORY que apunta a ese PDB.
- ``/DYNAMICBASE``:

```
/link /DEBUG /OUT:bin\main.exe build\main.obj
```