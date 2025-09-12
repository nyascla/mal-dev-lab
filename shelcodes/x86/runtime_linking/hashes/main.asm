[BITS 32]

_start:
    call geteip

geteip:
    pop edi
    lea edi, [edi - 5]


; llamada UNICODE
lea eax, [EDI + UNICODE_BUFFER]

push edi

push 2      
push eax
call rol_xor

mov eax, eax 
pop edi

; llamada ASCII
lea eax, [EDI + ASCII]

push edi

push 1
push eax
call rol_xor

mov eax, eax 
pop edi

ret


; ---------------------------------------
%include ".\rol_xor.asm"
; ---------------------------------------
UNICODE_BUFFER:
    ; lo hago asi para que cada caracter ocupes 2bytes y sea unicode string
    dw 'K', 'E', 'R', 'N', 'E', 'L', '3', '2', '.', 'D', 'L', 'L', 0

ASCII:
    db 'KERNEL32.DLL',0