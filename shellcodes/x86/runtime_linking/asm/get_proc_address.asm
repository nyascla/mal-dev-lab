; -----------------------------------
; TESTING
; -----------------------------------
; [BITS 32]
; _start:
;     call geteip
; geteip:
;     pop edx
;     lea edx, [edx - 5]
; main:
;     mov     eax, 0x46718AE6
;     push    eax
;     mov     eax, 0x764C0000
;     push    eax
;     call    _get_proc_address
; %include "./asm/rol_xor.asm"

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

; .\dlls\walking_export_table\README.md

; Offsets parametros
ModuleBase       equ 0x8
HashApi          equ 0xC

; Offsets variabels
AddressOfNames          equ -0x4
AddressOfNameOrdinals   equ -0x8
AddressOfFunctions      equ -0xC

; Offsets PE
offset_e_lfanew                equ 0x3c
offset_IMAGE_DATA_DIRECTORY   equ 0x78
offset_AddressOfFunctions      equ 0x1c 
offset_AddressOfNames          equ 0x20         
offset_AddressOfNameOrdinals   equ 0x24

_get_proc_address:
    ; -----------------------------------
    ; Init stack frame
    ; -----------------------------------
    push    ebp         ; guardo EBP del stack frame anterior
    mov     ebp, esp    ; inicializo el nuevo
    sub     esp, 0xC    ; reservamos espacio para dos variables locales

    ; -----------------------------------
    ; Conseguimos puntero a _IMAGE_EXPORT_DIRECTORY
    ; -----------------------------------
    mov     ebx, [ebp + ModuleBase]     ; BaseDll
    
    mov     dword esi, [ebx + offset_e_lfanew]          ; esi = Offset to NtHeader
    lea     esi, [ebx + esi]                            ; esi = NtHeader
    lea     esi, [esi + offset_IMAGE_DATA_DIRECTORY]    ; esi = Puntero to DataDirectory[0]
    mov     dword esi, [esi]    ; RVA to _IMAGE_EXPORT_DIRECTORY
    lea     esi, [ebx + esi]    ; esi = puntero to _IMAGE_EXPORT_DIRECTORY

    ; -----------------------------------
    ; Creamos Variables a los Arrays de _IMAGE_EXPORT_DIRECTORY
    ; -----------------------------------
    mov     edi, [esi + offset_AddressOfNames] ; edi = RVA to AddressOfNames
    lea     edi, [ebx + edi]   
    mov     [ebp + AddressOfNames], edi

    mov     edi, [esi + offset_AddressOfFunctions] ; edi = RVA to AddressOfFunctions
    lea     edi, [ebx + edi]
    mov     [ebp + AddressOfFunctions], edi

    mov     edi, [esi + offset_AddressOfNameOrdinals]   ; edi = RVA to AddressOfNameOrdinals
    lea     edi, [ebx + edi]
    mov     [ebp + AddressOfNameOrdinals], edi

    ; -----------------------------------
    ; Iteramos AddressOfNames
    ; -----------------------------------
    xor ecx, ecx
    .loop:    

        mov     edx, [ebp + AddressOfNames] ; Base of AddressOfNames
        lea     edx, [edx + ecx*4]          ; edx = puntero a array[ecx*4]
        mov     dword edx, [edx]            ; edx = RVA al nombre de la funcion ecx

        mov     ebx, [ebp + ModuleBase]     ; ebx = Base del modulo
        lea     edx, [ebx + edx]            ; edx = String con el nombre de la funcion

        push    1           ; 1 -> ASCII 2 -> UNICODE
        push    edx 
        call    _rol_xor    ; No modifica ECX
        
        cmp     eax, [ebp + HashApi]
        je .resove_export

        add     ecx, 1
        jne .loop


.resove_export:
    ; -----------------------------------
    ; RVA a la funcion exportada
    ; -----------------------------------
    mov     edx, [ebp + AddressOfNameOrdinals]  ; Base of AddressOfNameOrdinals
    lea     edx, [edx + ecx*2]                  ; edx = puntero a array[ecx*2]
    xor     eax, eax
    mov     word ax, [edx] ; eax = Ordinal

    mov     edx, [ebp + AddressOfFunctions]     ; Base of AddressOfFunctions
    lea     edx, [edx + eax*4]                  ; edx = puntero a array[ecx*2]
    mov     dword edx, [edx] ; edx = RVA a la funcino

    mov     ebx, [ebp + ModuleBase]     ; ebx = Base del modulo
    lea     eax, [ebx + edx]            ; eax = RETURN

    mov esp, ebp    ; limpia la pila
    pop ebp         ; restaura el viejo frame pointer
    ret             ; vuelve a la dirección de retorno