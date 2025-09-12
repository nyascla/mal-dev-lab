; -----------------------------------
; GET_MODULE_BASE
; -----------------------------------
; void* get_module_base(uint64_t hash_name)
; -----------------------------------
;   hash_name: RCX
; -----------------------------------
; return: RAX       = HMODULE || null

get_module_base:
    mov RDI, gs:[0x60]          ; RDI = _PEB
    mov RDI, [RDI + 0x018]      ; RDI = _PEB_LDR_DATA
    mov RDI, [RDI + 0x010]      ; RDI = InLoadOrderModuleList
    mov RSI, RDI                ; RSI = iterador

.next_module:
    ; puntero a UNICODE_STRING.Buffer del módulo
    mov R8, [RSI + 0x058 + 0x008]   
    
    push R8
    push RDI
    push RSI
    push RCX  
    
    mov RCX, R8
    mov RDX, 2
    call create_hash
    
    pop RCX
    pop RSI
    pop RDI
    pop R8
    
    cmp RAX, RCX
    je .equal             

    
    mov RSI, [RSI]          ; siguiente nodo en la lista          
    cmp RSI, RDI
    jne .next_module

    .equal:
        mov RAX, [RSI + 0x30]
        ret