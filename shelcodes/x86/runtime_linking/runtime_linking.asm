;-----------------------------------
; RUNTIME_LINKING
;-----------------------------------
; uint32_t runtime_linking(uint32_t hash_module, uint32_t hash_api)
;-----------------------------------
;       hash_api: [esp + 8]
;       hash_module: [esp + 4]
;-----------------------------------
; return: eax           = direccion de memoria de la funcion (hash_api)

runtime_linking:
    mov eax, [esp + 4]
    push eax
    call get_module_base
    mov ecx, eax

    mov eax, [esp + 8]
    push eax
    push ecx
    call get_function_from_module
    
    pop edx
    add esp, 8
    push edx

    ret


; -----------------------------------
%include ".\runtime_linking\get_module\get_module_base.asm"
%include ".\runtime_linking\hashes\rol_xor.asm" 
%include ".\runtime_linking\get_export\get_function_from_module.asm"
