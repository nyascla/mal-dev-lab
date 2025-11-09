[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

; -----------------------------------
; VARIABLES LOCALES
; -----------------------------------
BaseKernel32            equ -0x4  
BaseUser32              equ -0x8

GetProcAddress          equ -0xC
LoadLibraryA            equ -0x10

; -----------------------------------
; INIT Stack frame
; -----------------------------------
push    ebp
mov     ebp, esp
sub     esp, 0x10

; -----------------------------------
; Obtener base de kernell32.dll
; -----------------------------------
push    edx

mov     eax, [edx + KERNEL32]
push    eax ; (1º arg) module_hash
call    _get_module_handle ; void* get_module_handle(uint32_t module_hash);
mov     [ebp + BaseKernel32], eax
add     esp, 0x4

pop     edx

; -----------------------------------
; Resolver functions from Kernell32
; -----------------------------------
push    edx

lea     eax, [ebp + LoadLibraryA]
push    eax ; (3º arg) ptr_dest  
lea     eax, [edx + KERNEL32_HASHES]
push    eax ; (2º arg) ptr_source
mov     eax, dword [ebp + BaseKernel32]
push    eax ; (1º arg) base_module
call    _multi_import ; uint32_t multi_import(uint32_t base_module, ptr* ptr_source, ptr* ptr_dest)
add     esp, 0xC

pop     edx

; -----------------------------------
; Cargar USER32.dll
; -----------------------------------
push    edx

lea     ebx, [edx + USER32]
push    ebx ; (1º arg) module_name
mov     eax, [ebp + LoadLibraryA]
call    eax ; LoadLibraryA __stdcall (limpia la pila)
mov     [ebp + BaseUser32], eax

pop     edx

; -----------------------------------
; Recuperamos MESSAGEBOXA
; -----------------------------------
; FARPROC GetProcAddress(
;   [in] HMODULE hModule,
;   [in] LPCSTR  lpProcName
; );
push edx

lea     eax, [EDX + MESSAGEBOXA]
push    eax
mov     dword eax, [ebp + BaseUser32]
push    eax
call    [ebp + GetProcAddress]
mov     eax, eax

pop     edx

; -----------------------------------
; Llamamos MessageBoxA
; -----------------------------------
push 0
push 0
push 0
push 0
call eax

; -----------------------------------
; END
; -----------------------------------
mov     esp, ebp   
pop     ebp         
ret
           
; -----------------------------------
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM-shellcodes\runtime_linking\x86\exports.asm"
; -----------------------------------

KERNEL32:       dd 0x4b1ffe8e
USER32:         db 'user32.dll',0
MESSAGEBOXA:    db 'MessageBoxA',0

KERNEL32_HASHES:
    dd 0xC8E88006 ; LOADLIBRARYA
    dd 0x1FC062EF ; GETPROCADDRESS
    dd 0xFFFFFFFF



        




