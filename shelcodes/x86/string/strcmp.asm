[BITS 32]

_start:
    call geteip

geteip:
    pop edx
    lea edx, [edx - 5]

;-----------------------------------
; INI STRING
mov word [EDX + UNICODE], 18
mov word [EDX + UNICODE + 2], 20
lea edi ,[EDX + StringBuffer]
mov dword [EDX + UNICODE + 4], edi
mov edi, [EDX + UNICODE + 4]
lea esi, [EDX + ASCII]

call strcmp
; si eax tiene un 1 son iguales

;-----------------------------------
;   ESI -> puntero a ASCII string (1 byte por char)
;   EDI -> puntero a Unicode string (2 bytes por char)
;   AL = 1 si iguales, 0 si distintos
;-----------------------------------
strcmp:
    xor eax, eax          ; AL = 0, asumimos distintos
.compare_loop:
    mov al, [esi]         ; byte de ASCII
    mov bl, [edi]         ; palabra de Unicode
    cmp al, bl             ; comparamos con byte bajo de Unicode
    jne .not_equal
    cmp al, 0             ; fin de ASCII?
    je .equal             ; ambos terminadores -> iguales
    inc esi               ; siguiente byte ASCII
    add edi, 2            ; siguiente palabra Unicode
    jmp .compare_loop

.not_equal:
    xor al, al            ; AL = 0
    ret

.equal:
    mov al, 1             ; AL = 1
    ret

;-----------------------------------
ASCII:
    db 'kernel32.dll',0

StringBuffer:
    ; lo hago asi para que cada caracter ocupes 2bytes y sea unicode string
    dw 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0

UNICODE:
    ; Length = número de bytes usados (sin incluir null terminator)
    ; "hello.dll" tiene 9 caracteres -> 9*2 = 18 bytes
    dw 0x11             ; Length
    dw 0x22             ; MaximumLength (dejamos espacio para terminador)
    dd 0x33445566       ; Buffer (puntero al buffer UTF-16)