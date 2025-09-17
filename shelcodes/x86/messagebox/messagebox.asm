[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]


; -----------------------------------
; mov edx, [esp + 0x0]
; mov eax, [esp + 0x4]
; mov eax, [esp + 0x8]
; mov eax, [esp + 0xC]
; mov eax, [esp + 0x10]
push 0x00000011     ; esp + 10  BASE_KERNEL32
push 0x00000022     ; esp + C   BASE_USER32
push 0x00000033     ; esp + 8   DEF_GETPROCADDRESS
push 0x00000044     ; esp + 4   DEF_LOADLIBRARYA
push edx            ; esp + 0

; void* get_module_base(uint32_t hash_name)
mov eax, [edx + KERNEL32]
push eax
call get_module_base

mov [esp + 0x10], eax ; guardamos BASE_KERNEL32

; void* get_function_from_module(uint32_t module_base, uint32_t hash_api)
mov edx, [esp + 0x0] ; pone el base del blob en edx
mov ecx, [edx + GETPROCADDRESS]
mov eax, [esp + 0x10] ; BASE_KERNEL32
push ecx
push eax
call get_function_from_module

mov [esp + 0x8], eax ; guardamos DEF_GETPROCADDRESS

; void* get_function_from_module(uint32_t module_base, uint32_t hash_api)
mov edx, [esp + 0x0] ; pone el base del blob en edx
mov ecx, [edx + LOADLIBRARYA]
mov eax, [esp + 0x10] ; BASE_KERNEL32
push ecx
push eax
call get_function_from_module

mov [esp + 0x4], eax ; guardamos LOADLIBRARYA

; -----------------------------------
mov edx, [esp + 0x0] ; pone el base del blob en edx
mov edi, [esp + 0x4] ; DEF_LOADLIBRARYA
lea ebx, [EDX + USER32]
; HMODULE LoadLibraryA(
;   [in] LPCSTR lpLibFileName
; );
push ebx        ; lpLibFileName = puntero a 'user32.dll'
call edi        ; LoadLibraryA

mov [esp + 0xC], eax ; guardamos BASE_USER32

; -----------------------------------

mov edi, [esp + 0x8] ; DEF_GETPROCADDRESS
mov esi, [esp + 0xc] ; BASE_USER32
mov edx, [esp + 0x0] ; pone el base del blob en edx
lea ebx, [EDX + MESSAGEBOXA]
; FARPROC GetProcAddress(
;   [in] HMODULE hModule,
;   [in] LPCSTR  lpProcName
; );
push ebx
push esi
call edi ; GETPROCADDRESS
mov eax, eax

; int MessageBoxA(
;   [in, optional] HWND   hWnd,
;   [in, optional] LPCSTR lpText,
;   [in, optional] LPCSTR lpCaption,
;   [in]           UINT   uType
; );
push 0
push 0
push 0
push 0
call eax

; -----------------------------------
; Salto incondicional para seguir con la ejecucion
; void* get_module_base(uint32_t hash_name)
mov edx, [esp + 0x0] ; pone el base del blob en edx
mov eax, [edx + EXE_NAME_A]
push eax
call get_module_base

add eax, 0x00001131 ; entry point original
jmp eax

; -----------------------------------
%include ".\runtime_linking\runtime_linking.asm"
; -----------------------------------

KERNEL32_HASHES:
    KERNEL32:
        dd 0x4b1ffe8e
    LOADLIBRARYA:
        dd 0xC8E88006
    GETPROCADDRESS:
        dd 0x1FC062EF
    EXE_NAME: ; simple_mod_extra.exe
        dd 0x78058130
    EXE_NAME_A: ; messagebox.exe
        dd 0x0C4C8BE9

STRINGS:
    USER32:
        db 'user32.dll',0
    MESSAGEBOXA:
        db 'MessageBoxA',0




