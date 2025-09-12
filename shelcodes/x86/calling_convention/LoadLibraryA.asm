[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]


; HMODULE LoadLibraryA(
;   [in] LPCSTR lpLibFileName
; );
lea ebx, [EDX + USER32]
push ebx            ; lpLibFileName = puntero a 'user32.dll'
mov ecx, 0x75851C60
call ecx    ; LoadLibraryA

ret

USER32:
    db 'user32.dll',0