; [BITS 32]

; _start:
;     call geteip

; geteip:
;     pop edx
;     lea edx, [edx - 5]

; NASM, 32-bit Windows (stdcall/cdecl differences matter)
global _asm_add       ; nota el underscore

section .text
_asm_add:
    ; cdecl: args on stack: [esp+4]=a, [esp+8]=b
    mov eax, [esp+4]
    add eax, [esp+8]
    ret



