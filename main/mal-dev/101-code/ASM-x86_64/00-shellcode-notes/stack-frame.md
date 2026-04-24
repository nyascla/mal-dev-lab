# Stack Frame

## Montar

Guarda el Stack frame de la funcion llamadore e inicializa el Stack frame de la funcion actual

``` c
push    ebp         ; Guardar el stack frame de la funcion anterior
mov     ebp, esp    ; Inicializar el nuevo
sub     esp, 0x300  ; Reserva espacio para variables locales
```

## Desmontar

Destruye el Stack frame de la funcion actual y restaura el Stack frame de la funcion llamadora

> NOTA: 
> - en x86 (__stdcall) tambien habria que limpiar de la pila los parametros que se han pasado a la funcion
> - Segun la convencion restaurar los registros no volátiles que hayas modificado

``` c
mov esp, ebp    ; Limpia la pila
pop ebp         ; restaura el viejo frame pointer
ret             ; vuelve a la dirección de retorno
```

