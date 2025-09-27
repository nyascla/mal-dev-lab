; ============================================================
; RUNTIME_LINKING
; ------------------------------------------------------------
; uint32_t runtime_linking(uint32_t hash_module, ptr* hashes, ptr* destino)
; ------------------------------------------------------------
;   Descripción:
;       Carga funciones en tiempo de ejecución a partir del módulo indicado.
; 
;   Parámetros:
;       base_module  - [esp + 4] : Dirección base del módulo (hash del nombre del módulo).
;       ptr_source    - [esp + 8] : Puntero a lista de hashes de funciones a cargar.
;       ptr_dest      - [esp + c] : Puntero a lista donde se almacenarán las direcciones cargadas.
; 
;   Retorno:
;       uint32_t      - Número de funciones cargadas correctamente.
; ============================================================


_multi_import:
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
    call    _get_proc_address

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
