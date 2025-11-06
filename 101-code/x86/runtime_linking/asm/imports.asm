; ============================================================
; RUNTIME_LINKING
; ------------------------------------------------------------
; uint32_t multi_import(uint32_t base_module, ptr* ptr_source, ptr* ptr_dest)
; ------------------------------------------------------------
;   Descripción:
;       Carga funciones en tiempo de ejecución a partir del módulo indicado.
; 
;   Parámetros:
;       base_module     - [esp + 4] : Dirección base del módulo (hash del nombre del módulo).
;       ptr_source    - [esp + 8] : Puntero a lista de hashes de funciones a cargar.
;       ptr_dest      - [esp + c] : Puntero a lista donde se almacenarán las direcciones cargadas.
; 
;   Retorno:
;       uint32_t      - Número de funciones cargadas correctamente.
; ============================================================

; Parametros
base_module     equ 0x8
ptr_source      equ 0xC
ptr_dest        equ 0x10

; Variables

_multi_import:
    ; -----------------------------------
    ; Init stack frame
    ; -----------------------------------
    push    ebp         
    mov     ebp, esp   

    ; -----------------------------------
    ; Iteramos la lista de Hashes para importar
    ; -----------------------------------
    xor     ecx, ecx
    .loop:
        mov     ebx, [ebp + ptr_source]
        lea     ebx, [ebx + ecx*4]
        mov     ebx, dword [ebx]

        cmp     ebx, 0xFFFFFFFF
        je      .end_loop

        push ecx        ; contador

        push    ebx     ; hash_api  (2º arg)
        mov     eax, [ebp + base_module]
        push    eax     ; module_base (1er arg)
        call    _get_proc_address
        add     esp, 0x8

        pop ecx

        ; -----------------------------------
        ; Guardamos la direccion de la funcion
        ; -----------------------------------
        mov     ebx, [ebp + ptr_dest]
        lea     ebx, [ebx + ecx*4]
        mov     [ebx], eax

        add     ecx, 1
        jmp     .loop

.end_loop:
    ; -----------------------------------
    ; End stack frame
    ; -----------------------------------
    mov     eax, ecx
    mov     esp, ebp 
    pop     ebp
    ret         
      
