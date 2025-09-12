[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]


; -----------------------------------

push edx

; void* get_module_base(uint32_t hash_name)
mov eax, [edx + KERNEL32]
push eax
call get_module_base

pop edx
lea ebx, [edx + BASE_KERNEL32]
mov [ebx], eax ; guardamos BASE_KERNEL32
push edx

; void* get_function_from_module(uint32_t module_base, uint32_t hash_api)
mov ecx, [edx + GETPROCADDRESS]
push ecx
mov eax, [edx + BASE_KERNEL32]
push eax
call get_function_from_module

pop edx
lea ebx, [edx + DEF_GETPROCADDRESS]
mov [ebx], eax ; guardamos funcion GETPROCADDRESS
push edx

; void* get_function_from_module(uint32_t module_base, uint32_t hash_api)
mov ecx, [edx + LOADLIBRARYA]
push ecx
mov eax, [edx + BASE_KERNEL32]
push eax
call get_function_from_module

pop edx
lea ebx, [edx + DEF_LOADLIBRARYA]
mov [ebx], eax ; guardamos funcion LOADLIBRARYA
push edx

; -----------------------------------

mov edi, [edx + DEF_LOADLIBRARYA]
lea ebx, [EDX + USER32]
; HMODULE LoadLibraryA(
;   [in] LPCSTR lpLibFileName
; );
push ebx        ; lpLibFileName = puntero a 'user32.dll'
call edi        ; LoadLibraryA

pop edx
lea ebx, [edx + BASE_USER32]
mov [ebx], eax ; guardamos la base USER32
push edx

; -----------------------------------

mov edi, [edx + DEF_GETPROCADDRESS]
mov esi, [edx + BASE_USER32]
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

ret

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

BASE_KERNEL32:
    dd 0xFFFFFFFF
BASE_USER32:
    dd 0x33333333

FUNCTIONS:
    DEF_GETPROCADDRESS:
        dd 0x11111111
    DEF_LOADLIBRARYA:
        dd 0x22222222

STRINGS:
    USER32:
        db 'user32.dll',0
    MESSAGEBOXA:
        db 'MessageBoxA',0

