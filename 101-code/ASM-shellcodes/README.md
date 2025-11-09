## Lab Setup

1. [Visual Studio Code](https://code.visualstudio.com/Download)
    1. (ext) x86 and x86_64 Assembly
1. [Python 3.13](https://www.python.org/downloads/)
1. [nasm](https://www.nasm.us/pub/nasm/releasebuilds/)
1. [sclauncher](https://github.com/jstrosch/sclauncher)

---
1. [Build Tools for Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)
---

## Compilar

En VS Code, el atajo `Ctrl + Shift + B` despliega las tareas de compilación (build). Una vez ejecutada la tarea, los ficheros generados se guardarán en las carpetas de salida correspondientes del proyecto.

![alt text](image.png)

## Cabecera
```
; =============================================================================
;  get_proc_address
; -----------------------------------------------------------------------------
;  Prototipo en C:
;      void* get_proc_address(uint32_t module_base, uint32_t hash_api);
;
;  Descripción:
;      Busca en la tabla de exportaciones de un módulo PE una función cuyo 
;      nombre coincida con el hash dado. Devuelve la dirección de la función.
;
;  Argumentos (cdecl, en la pila):
;      [esp + 4]  -> uint32_t module_base   ; Dirección base del módulo en memoria
;      [esp + 8]  -> uint32_t hash_api      ; Hash del nombre de la función
;
;  Retorno:
;      eax = dirección de la función exportada (NULL si no se encuentra)
;
;  Convención de llamada:
;      __cdecl (caller limpia la pila)
;
; =============================================================================
```