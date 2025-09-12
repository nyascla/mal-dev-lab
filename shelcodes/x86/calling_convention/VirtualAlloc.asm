[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

push 0x40        ; flProtect = PAGE_EXECUTE_READWRITE
push 0x1000      ; flAllocationType = MEM_COMMIT
push 0x1000      ; dwSize = 4096 bytes
push 0x0         ; lpAddress = NULL

; LPVOID VirtualAlloc(
;   [in, optional] LPVOID lpAddress,            reservar en una direccion concreta
;   [in]           SIZE_T dwSize,               tamanyo a reservar
;   [in]           DWORD  flAllocationType,     elegir la forma en la que el SO reservara la memoria, pillar directamente memoria fisica o solo reservar direcciones virtuales
;   [in]           DWORD  flProtect             permisos de la memoria reservada
; );

mov ecx, 0x75FA65F0 ; VirtualAlloc
call ecx

test eax, eax
jz  fail
mov esi, eax

fail:
    ret
