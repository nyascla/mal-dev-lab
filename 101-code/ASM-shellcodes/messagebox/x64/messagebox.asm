; =============================================================================
;  x64_messagebox
; -----------------------------------------------------------------------------
;  Prototipo en C:
;      void x64_messagebox();
;
;  Descripción:
;      Ejecuta un MessageBox
;
;  Retorno:
;      EAX = NULL
;
;  Convención de llamada:
;      Microsoft x64
;
; =============================================================================

BITS 64

; Variables locales
BASE_KERNEL32           equ -0x08
DEF_LOADLIBRARYA        equ -0x10
DEF_GETPROCADDRESS      equ -0x18

BASE_USER32             equ -0x20
DEF_MESSAGEBOXA         equ -0x28


x64_messagebox:
    ; -----------------------------------
    ; Init stack frame
    ; -----------------------------------
    push    RBP                 ; guardo EBP del stack frame anterior
    mov     RBP, RSP            ; inicializo el nuevo
    sub     RSP, 0x28           ; reservamos espacio para 5 variables locales (5 * 8 bytes = 40 bytes)
    
    ; -----------------------------------
    ; Multi import
    ; -----------------------------------
    mov     RCX, 0x4B1FFE8E                 ; KERNEL32
    call    _x64_get_module_handle
    mov     [RBP + BASE_KERNEL32], RAX      ; BASE_KERNEL32

    mov     RCX, [RBP + BASE_KERNEL32]
    mov     RDX, 0xC8E88006                 ; LOADLIBRARYA
    call    _x64_get_proc_address
    mov     [RBP + DEF_LOADLIBRARYA], RAX   ; DEF_LOADLIBRARYA

    mov     RCX, [RBP + BASE_KERNEL32]
    mov     RDX, 0x1FC062EF                 ; GETPROCADDRESS
    call    _x64_get_proc_address
    mov     [RBP + DEF_GETPROCADDRESS], RAX     ; DEF_GETPROCADDRESS


    ; -----------------------------------
    ; HMODULE LoadLibraryA(
    ;   [in] LPCSTR lpLibFileName
    ; );
    lea     RCX, [rel USER32]               ; puntero a 'user32.dll'
    mov     RDI, [RBP + DEF_LOADLIBRARYA]
    sub     rsp, 0x28                       ; mantener rsp 16-byte aligned
    call    rdi                             ; LoadLibraryA
    add     rsp, 0x28                       ; mantener rsp 16-byte aligned
    mov     [RBP + BASE_USER32], rax        ; guardamos BASE_USER32

    ; -----------------------------------
    ; FARPROC GetProcAddress(
    ;   [in] HMODULE hModule,
    ;   [in] LPCSTR  lpProcName
    ; );
    mov     RCX, [RBP + BASE_USER32]
    lea     RDX, [rel MESSAGEBOXA]          ; puntero a 'MessageBoxA'
    mov     rdi, [RBP + DEF_GETPROCADDRESS]
    sub     rsp, 0x28                       ; mantener rsp 16-byte aligned
    call    rdi                             ; GETPROCADDRESS
    add     rsp, 0x28                       ; mantener rsp 16-byte aligned
    mov     [RBP + DEF_MESSAGEBOXA], rax    ; guardamos DEF_MESSAGEBOXA
  
    ; -----------------------------------
    ; int MessageBoxA(
    ;   [in, optional] HWND   hWnd,
    ;   [in, optional] LPCSTR lpText,
    ;   [in, optional] LPCSTR lpCaption,
    ;   [in]           UINT   uType
    ; );
    xor     RCX, RCX                    ; HWND = NULL
    lea     RDX, [rel USER32]           ; lpText
    lea     r8,  [rel MESSAGEBOXA]      ; lpCaption
    xor     r9d, r9d                    ; uType = 0
    sub     rsp, 0x28                       ; mantener rsp 16-byte aligned
    call    RAX
    add     rsp, 0x28                       ; mantener rsp 16-byte aligned

    ret

; ---------------------------------------
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM-shellcodes\runtime_linking\x64\x64_exports.asm"
; ---------------------------------------

KERNEL32_HASHES:
    dd 0xC8E88006 ; LOADLIBRARYA
    dd 0x1FC062EF ; GETPROCADDRESS
    dd 0xFFFFFFFF

; KERNEL32_HASHES:
;     KERNEL32:
;         dd 0x4b1ffe8e
;     LOADLIBRARYA:
;         dd 0xC8E88006
;     GETPROCADDRESS:
;         dd 0x1FC062EF
;     EXE_NAME: ; simple_mod_extra.exe
;         dd 0x78058130
;     EXE_NAME_A: ; messagebox.exe
;         dd 0x0C4C8BE9

STRINGS:
    USER32:
        db 'user32.dll',0
    MESSAGEBOXA:
        db 'MessageBoxA',0