;-----------------------------------
; RUNTIME_LINKING
;-----------------------------------
; uint32_t runtime_linking(uint32_t hash_module, ptr* hashes, ptr* destino)
;-----------------------------------
;       ptr_dest:       [esp + c]
;       ptr_source:     [esp + 8]
;       base_module:    [esp + 4]
;-----------------------------------


runtime_linking:
    mov eax, [esp + 0]
    mov eax, [esp + 4]
    mov eax, [esp + 8]
    mov eax, [esp + 0xc]

    xor     esi, esi
.loop:
    mov     eax, [esp + 0x8]        ; puntero a la lista de hashes
    mov     eax, dword [eax + esi]  ; iteramos y accedemos al valor en memoria

    cmp     eax, 0xFFFFFFFF
    je      .end_loop

    mov     ecx, [esp + 4]          ; base del modulo
    
    push esi

    push    eax         ; push hash_api  (2º arg)
    push    ecx         ; push module_base (1er arg)
    call    get_function_from_module

    pop esi

    ; almacenar el puntero devuelto (EAX) en [ebp - 8 - esi]
    mov     edi, [esp + 0xc]
    sub     edi, esi
    mov     dword [edi], eax

    add     esi, 4
    jmp     .loop

.end_loop:

    mov eax, 0x10101010
    ret 0xC

; -----------------------------------
%include ".\runtime_linking\get_module\get_module_base.asm"
%include ".\runtime_linking\hashes\rol_xor.asm" 
%include ".\runtime_linking\get_export\get_function_from_module.asm"
