[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

lea ebx, [EDX + aText]
push ebx            ; lpProcName = puntero a 'VirtualAlloc'
push 0x75f90000     ; hModule = base de kernel32.dll 


; FARPROC GetProcAddress(
;   [in] HMODULE hModule,
;   [in] LPCSTR  lpProcName
; );
mov ecx, 0x75fa6780 ; GetProcAddress
call ecx

test eax, eax
jz  fail
mov esi, eax

fail:
    ret

SCSTRINGS:
    aText:
        db 'VirtualAlloc',0
