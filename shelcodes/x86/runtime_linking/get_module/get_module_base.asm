; -----------------------------------
; GET_MODULE_BASE
; -----------------------------------
; void* get_module_base(uint32_t hash_name)
; -----------------------------------
;       hash_name: [esp + 4]            = uint32_t
; -----------------------------------
; return: eax                           = HMODULE || null

get_module_base:
    mov ebx, [esp + 4]

    mov edi, fs:[0x30]              ; edi = _PEB
    mov edi, [edi + 0x0C]           ; edi = _PEB_LDR_DATA
    mov edi, [edi + 0x0C]           ; edi = InLoadOrderModuleList
    mov esi, edi                    ; ESI = iterador

    next_module:
        ; puntero a UNICODE_STRING.Buffer del módulo
        mov edx, [esi + 0x2c + 0x04]   
        
        push ebx
        push edi
        push esi  
        
        push 2
        push edx
        call rol_xor
        
        pop esi
        pop edi
        pop ebx
        
        cmp eax, ebx
        je .equal             

        ; siguiente nodo en la lista
        mov esi, [esi]              ; ESI = Flink = siguiente nodo           
        cmp esi, edi
        jne next_module

    .equal:
        pop edx
        add esp, 4
        push edx

        mov eax, [esi + 0x18]
        ret

    .end:
        ; asumo que siempre lo encuentra