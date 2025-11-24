# Shellcode MessageBox x64 Segmentation Fault

Exception Code: 0xc0000005 (ACCESS_VIOLATION)

## Comportamiento Observado

El payload shellcode message box para x64 tiene una violacion de segmento 
Exception code: 0xc0000005

- Funciona correctamente con sclauncher
- Falla al integrar con código C compilado

> 197DEDE00DA: The instruction at 0x197DEDE00DA referenced memory at 0x370C66E8. The memory could not be read -> 00000000370C66E8 (exc.code c0000005, tid 416)

``` nasm
_x64_get_proc_address:
    
    mov     ESI, dword [RCX + 0x03C]    ; esi = Offset to NtHeader
    lea     RSI, [RCX + RSI]            ; esi = NtHeader
    
    ; ENTENDER PORQUE EL OFFSET ES 88 PORQUE LO HE ENCONTRADO POR PRUEBA Y ERROR
    mov     ESI, dword [RSI + 0x088]    ; esi = Offset to _IMAGE_EXPORT_DIRECTORY
    lea     RSI, [RCX + RSI]            ; esi = _IMAGE_EXPORT_DIRECTORY

    mov     EDI, dword [RSI + 0x020]    ; edi = Offset to array of names
    lea     EDI, dword [RCX + RDI]      ; edi = direccion del primer Offset al primer name
    
    mov     R9D, dword [RSI + 0x24]
    lea     R9D, dword [RCX + R9]       ; offset to ordinal

.loop:        
->    mov R8D, dword [RDI]    ; The instruction at 0x1CFC64A00DA referenced memory at 0x370C66E8. The memory could not be read -> 00000000370C66E8 (exc.code c0000005, tid 4540)
    lea R8, [RCX + R8]      ; esi = string name funcion
```

## Explicación del Bug

``` nasm
; CÓDIGO PROBLEMÁTICO
mov     EDI, dword [RSI + 0x020]    ; edi = Offset to array of names
lea     EDI, dword [RCX + RDI]      ; edi = direccion del primer Offset al primer name
```
En desarrollo: Kernel32 siempre estaba en direcciones de 32 bits
En producción: Al lanzar desde código C compilado, Kernel32 está en direcciones de 64 bits
Consecuencia: Al usar registros de 32 bits (EDI) se pierden las direcciones reales de 64 bits