; =============================================================================
;  get_proc_address
; -----------------------------------------------------------------------------
;  Prototipo en C:
;      void* get_proc_address(uint32_t module_base, uint32_t hash_api);
;
;  Descripción:
;      Busca en la tabla de exportaciones de un módulo PE una función cuyo 
;      nombre coincida con el hash dado. Devuelve la dirección de la función.
;
;  Argumentos (cdecl, en la pila):
;      [esp + 4]  -> uint32_t module_base   ; Dirección base del módulo en memoria
;      [esp + 8]  -> uint32_t hash_api      ; Hash del nombre de la función
;
;  Retorno:
;      eax = dirección de la función exportada (NULL si no se encuentra)
;
;  Convención de llamada:
;      __cdecl (caller limpia la pila)
;
; =============================================================================


_get_proc_address:
    mov     ebx, [esp + 4]      ; BaseDll
    
    mov     esi, [ebx + 0x3c]   ; esi = Offset to NtHeader
    lea     esi, [ebx + esi]    ; esi = NtHeader
    mov     esi, [esi + 0x78]   ; esi = Offset to _IMAGE_EXPORT_DIRECTORY
    lea     esi, [ebx + esi]    ; esi = _IMAGE_EXPORT_DIRECTORY

    mov     edi, [esi + 0x20]   ; edi = Offset to array of names
    lea     edi, [ebx + edi]    ; edi = direccion del primer Offset al primer name
    
    mov     ecx, [esi + 0x24]
    lea     ecx, [ebx + ecx]

    .loop:        
        mov     edx, [edi]
        lea     edx, [ebx + edx]    ; edx = string name funcion

        push    ebx
        push    edi
        push    ecx

        push    1
        push    edx 
        call    _rol_xor
        
        pop     ecx
        pop     edi
        pop     ebx
        
        cmp     eax, [esp + 8]
        je .resove_export

        add     ecx, 2
        add     edi, 4
        jne .loop


.resove_export:

    mov     ecx, [ecx + 2]      ; ordinal
    and     ecx, 0x0000FFFF
    imul    ecx, ecx, 4         ; ordinal * tam palabra
    sub     ecx, 4              ; vamos al inicio de la ultima palabra
    
    mov     edx, [esi + 0x1C]   ; offset to AddressOfFunctions
    add     ecx, edx            ; rva + ordinal
    lea     ecx, [ebx + ecx]            

    mov     ecx, [ecx]          ; rva a la funcion
    lea     eax, [ebx + ecx]    ; image base + rva



    ret