;-----------------------------------
; GET_FUNCTION_FROM_MODULE
;-----------------------------------
; void* get_function_from_module(uint64_t module_base, uint32_t hash_api)
;-----------------------------------
;   hash_api: RDX
;   module_base: RCX
;-----------------------------------
; return: RAX

get_function_from_module:
    
    mov ESI, dword [RCX + 0x03C]      ; esi = Offset to NtHeader
    lea RSI, [RCX + RSI]        ; esi = NtHeader
    ; ENTENDER PORQUE EL OFFSET ES 88 PORQUE LO HE ENCONTRADO POR PRUEBA Y ERROR
    mov ESI, dword [RSI + 0x088]      ; esi = Offset to _IMAGE_EXPORT_DIRECTORY
    lea RSI, [RCX + RSI]        ; esi = _IMAGE_EXPORT_DIRECTORY

    mov EDI, dword [RSI + 0x020]      ; edi = Offset to array of names
    lea EDI, dword [RCX + RDI]        ; edi = direccion del primer Offset al primer name
    
    mov R9D, dword [RSI + 0x24]
    lea R9D, dword [RCX + R9]        ; offset to ordinal

.loop:        
    mov R8D, dword [RDI]
    lea R8, [RCX + R8]        ; esi = string name funcion

    push RDI
    push RCX
    push RDX
    push RSI

    mov RCX, R8
    mov RDX, 1
    call create_hash

    pop RSI
    pop RDX
    pop RCX
    pop RDI
        
    cmp RAX, RDX
    je .equal

    ; add ecx, 2
    add RDI, 4
    add R9, 2
    jne .loop

.equal:
; buscamos 03f4
    mov R9W, word [R9 + 2]          ; ordinal
    and R9, 0x0000000000000FFF

    imul R9, R9, 4                  ; ordinal * tam palabra
    sub R9, 4                       ; vamos al inicio de la ultima palabra
    
    mov R10D, dword [RSI + 0x1C]    ; offset to AddressOfFunctions
    add R10, R9                     ; rva + ordinal
    lea R10, [RCX + R10*1]            

    mov R10D, dword [R10]           ; rva a la funcion
    lea RAX, [RCX + R10*1]          ; image base + rva

    ret