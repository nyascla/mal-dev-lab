[bits 64]

; ============================================================
; RUNTIME_LINKING (x64)
; ------------------------------------------------------------
; uint64_t multi_import(
;    uint64_t base_module,   ; RCX (hash 64-bit del módulo)
;    uint32_t* ptr_source,   ; RDX (puntero 64-bit a lista de DWORDs)
;    uint64_t* ptr_dest      ; R8  (puntero 64-bit a lista de QWORDs)
; );
; ============================================================

_multi_import:
    ; -----------------------------------
    ; Prólogo y guardado de registros
    ; -----------------------------------
    push    rbp
    mov     rbp, rsp
    
    push    r12             ; r12 = ptr_source (uint32_t*)
    push    r13             ; r13 = ptr_dest (uint64_t*)
    push    r14             ; r14 = base_module (uint64_t)
    push    r15             ; r15 = contador (counter)
    
    ; -----------------------------------
    ; Alinear pila y reservar Shadow Space
    ; -----------------------------------
    ; (Prólogo: 5 QWORDs pusheados = 40 bytes)
    ; La pila está 8 bytes desalineada. 
    ; Necesitamos 32 (shadow) + 8 (alineación) = 40 bytes (0x28).
    sub     rsp, 0x28
    
    ; -----------------------------------
    ; Mover argumentos a registros no volátiles
    ; -----------------------------------
    mov     r14, rcx        ; r14 = base_module (64-bit)
    mov     r12, rdx        ; r12 = ptr_source (puntero a DWORDs)
    mov     r13, r8         ; r13 = ptr_dest (puntero a QWORDs)
    xor     r15, r15        ; r15 = 0 (contador)

; -----------------------------------
; Iteramos la lista de Hashes (DWORDs)
; -----------------------------------
.loop:
    ; Cargar el hash de 32 bits (DWORD)
    ; (Usamos EAX como temporal)
    mov     eax, dword [r12 + r15*4] ; <-- CAMBIO: dword y r15*4

    ; Comprobar el terminador de 32 bits
    cmp     eax, 0xFFFFFFFF
    je      .end_loop

    ; -----------------------------------
    ; Llamar a _get_proc_address
    ; Args: RCX = base_module (64-bit), RDX = hash_api (32-bit)
    ; -----------------------------------
    mov     rcx, r14        ; 1er arg: base_module (64-bit)
    mov     edx, eax        ; 2º arg: hash_api (32-bit)
    call    _get_proc_address

    ; -----------------------------------
    ; Guardamos la direccion de 64 bits (RAX)
    ; -----------------------------------
    mov     [r13 + r15*8], rax

    ; Siguiente iteración
    add     r15, 1
    jmp     .loop

.end_loop:
    ; -----------------------------------
    ; Epílogo y retorno
    ; -----------------------------------
    mov     rax, r15        ; Valor de retorno (el contador)
    
    add     rsp, 0x28       ; Limpiar shadow space
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbp
    ret