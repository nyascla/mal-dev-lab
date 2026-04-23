section .text
global suma_y_multiplica

suma_y_multiplica:
    push ebp          ; Salva el base pointer
    mov ebp, esp      ; Establece nuevo base pointer

    mov eax, [ebp+8]  ; Primer argumento (a) en eax
    add eax, [ebp+12] ; Suma segundo argumento (b)
    shl eax, 1        ; Multiplica por 2 (shift left)

    pop ebp           ; Restaura base pointer
    ret               ; Retorna, valor en eax