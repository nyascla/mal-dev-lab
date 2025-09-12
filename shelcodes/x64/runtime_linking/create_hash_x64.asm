; ---------------------------------------
; CREATE_HASH_UTF_16
; ---------------------------------------
; uint32_t create_hash(void* str, int bytes_for_character)
; ---------------------------------------
;   bytes_for_character: RDX      = 1 o 2 bytes cada caracter
;   str: RCX                      = puntero a string null-terminated
; ---------------------------------------
; return: RAX                     = hash de 32 bits

create_hash:
    xor RAX, RAX        ; result = 0

.next_char: 
    mov R8B, [RCX]      ; cargar siguiente carácter
    cmp R8B, 0          ; final string?
    je .done   

    cmp R8B, 'A'
    jb .is_lower
    cmp R8B, 'Z'
    ja .is_lower
    or R8B, 0x20        ; setea bit 5 → minúscula  

.is_lower:
    rol EAX, 7          ; result = rol(result,7) | notar que uso EAX para que se mantenga a 32 bits
    movzx R8, R8B       ; extender BL a 64 bits
    xor RAX, R8         ; result ^= char
    add RCX, RDX        ; avanzamos la string
    jmp .next_char

.done:         
    ret
