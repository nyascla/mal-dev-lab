# x86 Calling Conventions

- ``Argumentos``: Por pila (right-to-left)
- ``Registro retorno``: EAX
- ``Limpieza de pila``: Depende de la convencion
    - *__stdcall*:  callee limpia la pila.
    - *__cdecl*:    caller limpia la pila. [ la convención por defecto en MSVC para funciones en C ]

En x86 existen calling conventions que definen quién debe preservar qué registros:
    - cdecl / stdcall (Windows, Linux):
        - Los callers deben guardar EAX, ECX, EDX si los necesitan.
        - Los callees deben preservar EBX, ESI, EDI, EBP.

## Ejemplos Limpieza de pila

```nasm
    ; __stdcall
    ; ...
    ret 16  ; callee limpia la pila
```

```nasm
    ; __cdecl
    call add
    add esp, 8  ; caller limpia los 2 argumentos
```

