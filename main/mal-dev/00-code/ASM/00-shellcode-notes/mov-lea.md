# (MOV vs LEA) Data movement 

`LEA`: Calcula una dirección 
`MOV`: Mueve datos entre registros y memoria.

## LEA (Load Effective Address)

> No copia datos

Calcula una dirección y la carga en un registro, Nunca accede a memoria

`[]`: Indica cálculo de dirección (como un paréntesis matemático).

``` c
lea eax, ebx                ; eax = ebx
lea eax, [ebx + ecx*4]      ; eax = ebx + ecx*4
lea eax, [ebx + 8]          ; eax = ebx + 8
lea eax, [ebx + ecx*2 + 16] ; eax = ebx + ecx*2 + 16
```

## MOV

> No calcula direcciones

Copiar un valor de un lugar a otro.

`[]`: Indica acceso a memoria. Lee o escribe en la dirección contenida

### To Registro

``` c
mov eax, ebx            ; eax = ebx
mov eax, 0x12345678     ; eax = constante
mov al, 0xFF            ; 8 bits menos significativos de eax = 0xFF
mov ah, 0xFF            ; 8 bits mas significativos de eax = 0xFF
mov eax, dword [ebx + 0x0]    ; eax = valor en la dirección de memoria [ebx + 0x0](memoria)
```

### To Memoria 
``` c
mov [ebx + 0x0], eax      ; [ebx + 0x0](memoria) = eax
// Memoria to Memoria
// Moveremos el cotenido de memoria donde apunto ebx 
// A la direccion de memoria donde apunta ecx
// Usaremos eax como registro intermedio
mov eax, dword [ebx]      ; eax = [ebx](memoria)
mov dword [ecx], eax      ; [ecx](memoria) = eax
```