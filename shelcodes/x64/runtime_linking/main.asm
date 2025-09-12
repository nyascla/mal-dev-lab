;---------------------------------------
; RUNTIME-LINKING x64
;---------------------------------------
BITS 64

_main:
    mov ECX, 0x4B1FFE8E
    call get_module_base
    mov R12,RAX

    mov RCX, R12
    mov RDX, 0xC8E88006
    call get_function_from_module

    ret

%include ".\create_hash_x64.asm"
%include ".\get_module_base_x64.asm"
%include ".\get_function_from_module_x64.asm"
