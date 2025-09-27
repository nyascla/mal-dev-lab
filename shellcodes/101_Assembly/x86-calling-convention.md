# x86 Calling Conventions

- ``Argumentos``: Por pila (right-to-left)
- ``Registro retorno``: EAX
- ``Limpieza de pila``: Depende de la convencion
    - *__stdcall*: callee limpia la pila.
    - *__cdecl*: caller limpia la pila. [ la convención por defecto en MSVC para funciones en C ]


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

