;-----------------------------------
; GET_FUNCTION_FROM_MODULE
;-----------------------------------
; void* get_function_from_module(uint32_t module_base, uint32_t hash_api)
;-----------------------------------
;       hash_api: [esp + 8]
;       module_base: [esp + 4]
;-----------------------------------
; return: eax 

get_function_from_module:
    mov ebx, [esp + 4]      ; BaseDll
    
    mov esi, [ebx + 0x3c]   ; esi = Offset to NtHeader
    lea esi, [ebx + esi]    ; esi = NtHeader
    mov esi, [esi + 0x78]   ; esi = Offset to _IMAGE_EXPORT_DIRECTORY
    lea esi, [ebx + esi]    ; esi = _IMAGE_EXPORT_DIRECTORY

    mov edi, [esi + 0x20]   ; edi = Offset to array of names
    lea edi, [ebx + edi]    ; edi = direccion del primer Offset al primer name
    
    mov ecx, [esi + 0x24]
    lea ecx, [ebx + ecx]

    fun_loop:        
        mov edx, [edi]
        lea edx, [ebx + edx]    ; edx = string name funcion

        push ebx
        push edi
        push ecx

        push 1
        push edx 
        call rol_xor
        
        pop ecx
        pop edi
        pop ebx
        
        cmp eax, [esp + 8]
        je .equal

        add ecx, 2
        add edi, 4
        jne fun_loop

    .equal:
        mov ecx, [ecx + 2]      ; ordinal
        and ecx, 0x0000FFFF
        imul ecx, ecx, 4        ; ordinal * tam palabra
        sub ecx, 4              ; vamos al inicio de la ultima palabra
        
        mov edx, [esi + 0x1C]   ; offset to AddressOfFunctions
        add ecx, edx            ; rva + ordinal
        lea ecx, [ebx + ecx]            

        mov ecx, [ecx]          ; rva a la funcion
        lea eax, [ebx + ecx]    ; image base + rva

        pop edx
        add esp, 8
        push edx

        ret