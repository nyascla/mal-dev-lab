; ============================================================
;  GET_MODULE_BASE
; ------------------------------------------------------------
;  Prototipo en C:
;       void* get_module_handle(uint32_t hash_name);
;
;  Parámetros (cdecl, stack):
;       [esp + 4]   -> uint32_t hash_name    ; Hash del nombre del módulo
;
;  Retorno:
;       eax         -> HMODULE (base address del módulo) 
;                      o NULL si no se encuentra
; ============================================================

; Parametros
hash_name equ 0x8
; Variables locales

; Offsets PEB
offset_PEB equ 0x30
offset_PEB_LDR_DATA equ 0xC
offset_InLoadOrderModuleList equ 0xC


_get_module_handle:
    ; -----------------------------------
    ; Init stack frame
    ; -----------------------------------
    push    ebp         
    mov     ebp, esp   

    mov edi, fs:[offset_PEB]                        ; edi = _PEB
    mov edi, [edi + offset_PEB_LDR_DATA]            ; edi = _PEB_LDR_DATA
    mov edi, [edi + offset_InLoadOrderModuleList]   ; edi = InLoadOrderModuleList
    mov esi, edi                    ; ESI = iterador

    ; -----------------------------------
    ; Iteramos InLoadOrderModuleList
    ; -----------------------------------
    .loop:
        mov edx, dword [esi + 0x2c + 0x04]      ; puntero a UNICODE_STRING.Buffer del módulo     
        
        push 2          ; 1 -> ASCII 2 -> UNICODE
        push edx
        call _rol_xor   ; no modifica ecx, esi, edi
        
        mov ebx, [ebp + hash_name]
        cmp eax, ebx
        je .equal             

        mov dword esi, [esi]  ; ESI = Flink = siguiente nodo           
        cmp esi, edi
        jne .loop

        jmp .error

    .equal:
        mov eax, [esi + 0x18]
        mov esp, ebp
        pop ebp
        ret

    .error:
        mov eax, 0xFFFFFFFF
        mov esp, ebp
        pop ebp
        ret

