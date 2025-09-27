# Stack Frame

````
push    ebp         ; guardo ebp del stack frame anterior
mov     ebp, esp    ; inicializo el nuevo
sub     esp, 0x300  ; mejor que sobre
```


````
; -----------------------------------
mov esp, ebp    ; limpia la pila
pop ebp         ; restaura el viejo frame pointer
ret             ; vuelve a la dirección de retorno
```