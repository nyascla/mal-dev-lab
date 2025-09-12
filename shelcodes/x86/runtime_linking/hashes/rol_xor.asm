; ---------------------------------------
; ROL_XOR
; ---------------------------------------
; uint32_t rol_xor(void* str, int bytes_for_character)
; ---------------------------------------
;   bytes_for_character: [ESP + 8]      = Numero de bytes por letra
;   str: [ESP + 4]                      = Puntero a string null-terminated
; ---------------------------------------
; return: EAX                           = Hash de 32 bits
; ---------------------------------------

rol_xor:
    mov edx, [ESP + 4]
    xor eax, eax        ; result = 0

.next_char:
    mov bl, [edx]       ; Carga el byte menos significativo
    cmp bl, 0           ; Es el byte de final de string? (bl - 0)
    je .done            ; Salta si ZF (Zero Flag) = 1

    cmp bl, 'A'         ;
    jb .skip_lower      ; JB (Jump if Below)
    cmp bl, 'Z'
    ja .skip_lower      ; JA (Jump if Above)
    or bl, 0x20         ; Setea bit 5 a 1
                        ; A = 0100 0001
                        ; a = 0110 0001

.skip_lower:
    rol eax, 7          ; result = rol(result,7)
    movzx ebx, bl       ; extender BL a 32 bits
    xor eax, ebx        ; result ^= char
    add edx, [ESP + 8]  ; siguiente carácter
    jmp .next_char

.done:
    pop edx             ; recuperamos la direccion de retorno
    add esp, 8          ; 2 argumentos × 4 bytes
    push edx
    
    ret


