[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

; llamaremos a messagebox
lea ebx, [EDX + aText]
lea ecx, [EDX + aTitle]

push 0
push ebx
push ecx
push 0

; int MessageBoxA(
;   [in, optional] HWND   hWnd,
;   [in, optional] LPCSTR lpText,
;   [in, optional] LPCSTR lpCaption,
;   [in]           UINT   uType
; );
mov eax, 0x764EAD20
call eax

ret

SCSTRINGS:
    aText:
        db 'text',0
    aTitle:
        db 'title',0

