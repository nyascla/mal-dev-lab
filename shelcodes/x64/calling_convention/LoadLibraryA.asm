BITS 64



; HMODULE LoadLibraryA(
;   [in] LPCSTR lpLibFileName
; );

sub rsp, 32     ; shadow space
sub rsp, 8      ; alineado           

lea rcx, [rel ASCII]        
mov rax, 0x0000000000452D80     
call rax     
add rsp, 40                


ASCII:
    db 'user32.dll',0


;     Address=0000000000452D80
; Type=Export
; Ordinal=1012
; Symbol=LoadLibraryA


; Address=00000000005B2D80
; Type=Export
; Ordinal=1012
; Symbol=LoadLibraryA
