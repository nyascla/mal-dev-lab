;---------------------------------------
; RUNTIME-LINKING x64
;---------------------------------------
BITS 64

_main:

    push 0x4444     ; esp + 18  BASE_USER32
    push 0x3333     ; esp + 10  DEF_GETPROCADDRESS
    push 0x2222     ; esp + 8   DEF_LOADLIBRARYA
    push 0x1111     ; esp + 0   BASE_KERNEL32
    
    mov ECX, 0x4B1FFE8E ; KERNEL32
    call get_module_base
    mov [rsp + 0x0] ,RAX ; BASE_KERNEL32

    mov RCX, [rsp + 0x0]
    mov RDX, 0xC8E88006 ; LOADLIBRARYA
    call get_function_from_module
    mov [rsp + 0x8] ,RAX ; DEF_LOADLIBRARYA

    mov RCX, [rsp + 0x0]
    mov RDX, 0x1FC062EF ; GETPROCADDRESS
    call get_function_from_module
    mov [rsp + 0x10] ,RAX ; DEF_GETPROCADDRESS

    ; HMODULE LoadLibraryA(
    ;   [in] LPCSTR lpLibFileName
    ; );
    lea rcx, [rel USER32] ; puntero a 'user32.dll'
    mov rdi, [rsp + 0x8]
    sub rsp, 0x28                 ; mantener rsp 16-byte aligned
    call rdi ; LoadLibraryA
    add rsp, 0x28                 ; mantener rsp 16-byte aligned
    mov [rsp + 0x18], rax ; guardamos BASE_USER32

    ; FARPROC GetProcAddress(
    ;   [in] HMODULE hModule,
    ;   [in] LPCSTR  lpProcName
    ; );
    mov rcx, [rsp + 0x18]
    lea rdx, [rel MESSAGEBOXA] ; puntero a 'user32.dll'
    mov rdi, [rsp + 0x10]
    sub rsp, 0x28                 ; mantener rsp 16-byte aligned
    call rdi ; GETPROCADDRESS

    ; int MessageBoxA(
    ;   [in, optional] HWND   hWnd,
    ;   [in, optional] LPCSTR lpText,
    ;   [in, optional] LPCSTR lpCaption,
    ;   [in]           UINT   uType
    ; );

    xor rcx, rcx           ; HWND = NULL
    lea rdx, [rel USER32]     ; lpText
    lea r8,  [rel MESSAGEBOXA]   ; lpCaption
    xor r9d, r9d           ; uType = 0
    sub rsp, 0x40
    call RAX


    ret

%include ".\create_hash_x64.asm"
%include ".\get_module_base_x64.asm"
%include ".\get_function_from_module_x64.asm"


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