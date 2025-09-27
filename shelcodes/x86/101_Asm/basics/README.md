# Basicos

## Registros

| Registro 32-bit | 16-bit | 8-bit alto/bajo | Uso típico                                                          |
| --------------- | ------ | --------------- | ------------------------------------------------------------------- |
| EAX             | AX     | AH/AL           | Acumulador, operaciones aritméticas, retorno de funciones           |
| EBX             | BX     | BH/BL           | Base, registro calificador, preservado por la convención de llamada |
| ECX             | CX     | CH/CL           | Contador, bucles, operaciones de desplazamiento, argumentos         |
| EDX             | DX     | DH/DL           | Datos, operaciones de E/S, multiplicación/división                  |
| ESI             | SI     | —               | Fuente de datos, acceso a arrays, operaciones de cadena             |
| EDI             | DI     | —               | Destino de datos, operaciones de cadena                             |
| EBP             | BP     | —               | Base pointer / frame pointer, preservado                            |
| ESP             | SP     | —               | Stack pointer, siempre alineado a 4 bytes                           |

## Stack Frame


## Import Asm From C

Cada ejecutable (.exe) o módulo (.dll) tiene su propia IAT.

Como el linker pone la direccion del codigo asm en la IAT en la Imagen en memoria del proceso C


## Data movement (MOV vs LEA)

### MOV
1. Su función principal es copiar un valor de un lugar a otro.
2. Puede mover datos entre registros, memoria y registros, o memoria y registros.
3. Importante: no calcula direcciones, simplemente copia el contenido tal cual.

``` nasm
; MOV entre registros
mov eax, ebx        ; eax = ebx

; MOV inmediato a registro
mov eax, 0x12345678 ; eax = constante

; MOV desde memoria a registro
mov eax, [ebx + 0x0]      ; eax = valor en la dirección apuntada por ebx + 0x0

; MOV desde registro a memoria
mov [ebx + 0x0], eax      ; memoria[ebx + 0x0] = eax

; MOV entre memoria y memoria no permitido directamente
; Necesita un registro intermedio
mov eax, [ebx]
mov [ecx], eax

; MOV con registros parciales
mov al, 0xFF        ; parte baja de eax
```

### LEA

1. No copia datos, sino que calcula una dirección según la expresión de direccionamiento y la carga en un registro.

``` nasm
lea eax, [ebx]              ; eax = dirección contenida en ebx
lea eax, [ebx + ecx*4]      ; eax = ebx + ecx*4
lea eax, [ebx + 8]          ; eax = ebx + 8
lea eax, [ebx + ecx*2 + 16] ; eax = ebx + ecx*2 + 16
```
