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

base_module     equ -0x08
ptr_source      equ -0x10
ptr_dest        equ -0x18

_multi_import:
    ; -----------------------------------
    ; Prólogo y guardado de registros
    ; -----------------------------------
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x18 

    mov     [rbp + base_module], RCX
    mov     [rbp + ptr_source], RDX
    mov     [rbp + ptr_dest], R8

    
; -----------------------------------
; Iteramos la lista de Hashes (DWORDs)
; -----------------------------------
    xor     r15, r15

.loop:
    ; Cargar el hash de 32 bits (DWORD)
    ; (Usamos EAX como temporal)
    mov     rdx, [rbp + ptr_source]
    lea     rdx, [rdx + r15*4]
    mov     eax, dword [rdx]

    ; Comprobar el terminador de 32 bits
    cmp     eax, 0xFFFFFFFF
    je      .end_loop

    ; -----------------------------------
    ; Llamar a _get_proc_address
    ; Args: RCX = base_module (64-bit), RDX = hash_api (32-bit)
    ; -----------------------------------
    mov     rcx, [rbp + base_module]    ; 1er arg: base_module (64-bit)
    mov     edx, eax                    ; 2º arg: hash_api (32-bit)
    call    _x64_get_proc_address

    ; -----------------------------------
    ; Guardamos la direccion de 64 bits (RAX)
    ; -----------------------------------
    mov     rdx, [rbp + ptr_dest]
    mov     [rdx + r15*8], rax

    

    ; Siguiente iteración
    add     r15, 1
    jmp     .loop

.end_loop:
    ; -----------------------------------
    ; Epílogo y retorno
    ; -----------------------------------
    mov     rax, r15        ; Valor de retorno (el contador)

    mov rsp, rbp    ; limpia la pila
    pop rbp         ; restaura el viejo frame pointer
    ret             ; vuelve a la dirección de retorno