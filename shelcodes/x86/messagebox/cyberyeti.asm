[BITS 32]

mainentrypoint:
call geteip
geteip:
    pop edx
    lea edx, [edx - 5]

push edx
mov ebx, 0x4b1ffe8e ; kernel32
call getmoduleaddress
pop edx

mov ebp, eax
push ebp
push edx

lea esi, [EDX + KERNEL32HASHTABLE]
lea edi, [EDX + KERNEL32FUNCTIONS]
call getapiaddresses
pop edx
pop ebp 

push edx
lea ecx, [EDX+aLoadLibrary]
push ecx
call [EDX+LoadLibrary]
mov ebp, eax ; mueve el handler de LoadLibrary a ebp
pop edx

; Busca la direccion de MessageBox
push edx
lea esi, [EDX + USER32HASHTABLE]
lea edi, [EDX + USER32FUNCTIONS] ; aqui ira la direccion de MessageBox
call getapiaddresses
pop edx

; call messagebox
push edx
push 0
lea ecx, [EDX+aCaption]
push ecx
lea ecx, [EDX+aMessage]
push ecx
push 0
call [EDX+MessageBoxA]
pop edx

push 0
call [EDX+ExitProcess]

; returns module base in EAX
; EBP = Hash of desired module
getmoduleaddress:
;walk PEB find target module
cld
xor edi, edi
mov edi, [FS:0x30]
mov edi, [edi+0xC]
mov edi, [edi+0x14]

next_module_loop:
mov esi, [edi+0x28]
xor edx, edx

module_hash_loop:
lodsw
test al, al
jz end_module_hash_loop
cmp al, 0x41
jb end_hash_check
cmp al, 0x5A
ja end_hash_check
or al, 0x20
end_hash_check:
rol edx, 7
xor dl, al
jmp module_hash_loop

end_module_hash_loop:

cmp edx, ebx
mov eax, [edi+0x10]
mov edi, [edi]
jnz next_module_loop

ret

; Resolves function pointers from module based on hashes pointed to by ESI 
; EBP = module base 
; ESI = array of checksums
; EDI = dest array of function pointers
getapiaddresses:
mov edx, ebp
add edx, [edx+3Ch]
mov edx, [edx+78h]
add edx, ebp
mov ebx, [edx+20h]
add ebx, ebp
xor ecx, ecx

load_api_hash:
push edi
push esi
mov esi, [esi]

load_api_name:
mov edi, [ebx]
add edi, ebp
push edx
xor edx, edx

create_hash_loop:
rol edx, 7
xor dl, [edi]
inc edi
cmp byte [edi], 0
jnz create_hash_loop

xchg eax, edx
pop edx
cmp eax, esi
jz load_api_addy
add ebx, 4
inc ecx
cmp [edx+18h], ecx
jnz load_api_name
pop esi
pop edi
ret

load_api_addy:
pop esi
pop edi
lodsd
push esi
push ebx
mov ebx, ebp
mov esi, ebx
add ebx, [edx+24h]
lea eax, [ebx+ecx*2]
movzx eax, word [eax]
lea eax, [esi+eax*4]
add eax, [edx+1ch]
mov eax, [eax]
add eax, esi
stosd
pop ebx
pop esi
add ebx, 4
inc ecx
cmp dword [esi], 0FFFFh
jnz load_api_hash

ret

KERNEL32HASHTABLE:
    dd 0x95902b19 ; ExitProcess
    dd 0xc8ac8026 ; LoadLibraryA
    dw 0xFFFF

KERNEL32FUNCTIONS:
    ExitProcess:
        dd 0x00000001
    LoadLibrary:
        dd 0x00000002


USER32HASHTABLE:
    dd 0xabbc680d
    dw 0xFFFF

USER32FUNCTIONS:
    MessageBoxA:
        dd 0x00000001

SCSTRINGS:
    aLoadLibrary:
        db 'user32.dll',0
    aMessage:
        db 'here',0
    aCaption:
        db 'abc',0