;-----------------------------------
; GET_FUNCTION_FROM_MODULE
;-----------------------------------
; void* _x64_get_proc_address(uint64_t module_base, uint32_t hash_api)
;-----------------------------------
;   hash_api: RDX
;   module_base: RCX
;-----------------------------------
; return: RAX

_x64_get_proc_address:
    ;  0x3c DWORD e_lfanew;
    xor     rsi, rsi
    mov     esi, dword [rcx + 0x03C]    ; rsi = e_lfanew (Offset to NtHeader)
    lea     rsi, [rcx + rsi]            ; rsi = NtHeader
   
    ; IMAGE_DIRECTORY_ENTRY_EXPORT
    ;     struct _IMAGE_DATA_DIRECTORY {
    ;     0x00 DWORD VirtualAddress;
    ;     0x04 DWORD Size;
    ; };
    mov     esi, dword [rsi + 0x88]     ; esi = IMAGE_DIRECTORY_ENTRY_EXPORT(VirtualAddress)
    ; esi = Offset a la tabla de exports del modulo
    
    lea     rsi, [rcx + rsi]            ; rsi = _IMAGE_EXPORT_DIRECTORY

    ;  0x20 DWORD AddressOfNames;
    xor     rdi, rdi
    mov     edi, dword [rsi + 0x20]    ; edi = Offset to array of names
    lea     rdi, [rcx + rdi]     ; rdi = direccion del primer Offset al primer name
    
    ; 0x24 DWORD AddressOfNameOrdinals;
    xor     r9,r9
    mov     r9d, dword [rsi + 0x24]
    lea     r9, [rcx + R9]       ; offset to ordinal

.loop:        
    mov R8D, dword [RDI]
    lea R8, [RCX + R8]      ; esi = string name funcion

    push RDI
    push RCX
    push RDX
    push RSI

    mov RCX, R8
    mov RDX, 1
    call create_hash    ; x64_rol_xor.asm

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