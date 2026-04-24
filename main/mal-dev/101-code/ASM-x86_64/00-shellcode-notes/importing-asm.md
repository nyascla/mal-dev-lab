# Import Asm From C

Cada ejecutable (.exe) o módulo (.dll) tiene su propia IAT.

Cuando el linker pone la dirección del código asm en la IAT o resuelve símbolos internos, eso queda fijado en la imagen PE que se mapea en memoria por el loader de Windows.


``` bash
nasm -f win32 "asm/export.asm" -o "build/export.obj"
```
- Genera un objeto COFF (PE/COFF) con secciones (.text, .data, etc.), tabla de símbolos, y entradas de relocación donde el código o datos necesitan direcciones aún no resueltas.

- Las etiquetas que expones (global / public) aparecen en la tabla de símbolos del .obj. No hay direcciones finales aún, sólo referencias y offsets relativos dentro del objeto.

``` bash
cl /Zi /Fo"build\main.obj" /c main.c
```
- El compilador genera otro objeto COFF.

- Las referencias a funciones externas (las funciones asm) quedan como símbolos no resueltos y referencias (relocations) apuntando a esos nombres.

``` bash
link /OUT:"bin\main.exe" build\main.obj build\export.obj 
```
- Para símbolos resueltos entre objetos del mismo link (C ↔ ASM), el linker escribe direcciones directas en el código/constantes donde había relocations (por ejemplo llamadas call o loads mov [addr], ...).

- Para funciones externas que provienen de DLLs (API de Windows), el linker no escribe la dirección final (porque la DLL se carga en tiempo de ejecución). En su lugar:

- Reserva y/o inicializa la IAT con thunks (entradas que el loader sobrescribirá con direcciones reales).

## Loader

Resolución de imports: el loader busca en la Export Table de la DLL las funciones importadas y escribe sus direcciones reales en las entradas de la IAT del módulo. A partir de ese momento, las llamadas indirectas a través de la IAT (call [IAT+offset]) invocan la rutina real en la DLL.