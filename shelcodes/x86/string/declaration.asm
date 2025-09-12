StringBuffer:
    ; lo hago asi para que cada caracter ocupes 2bytes y sea unicode string
    dw 'K', 'E', 'R', 'N', 'E', 'L', '3', '2', '.', 'D', 'L', 'L', 0

UNICODE:
    ; Length = número de bytes usados (sin incluir null terminator)
    ; "hello.dll" tiene 9 caracteres -> 9*2 = 18 bytes
    dw 0x11             ; Length
    dw 0x22             ; MaximumLength (dejamos espacio para terminador)
    dd 0x33333333       ; Buffer (puntero al buffer UTF-16)

SCSTRINGS:
    aModule:
        db 'KERNEL32.DLL',0