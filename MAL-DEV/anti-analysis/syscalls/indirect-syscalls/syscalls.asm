EXTERN sysAddrNtAllocateVirtualMemory:QWORD         ; The actual address of the NtAllocateVirtualMemory syscall in ntdll.dll.
EXTERN sysAddrNtWriteVirtualMemory:QWORD            ; The actual address of the NtWriteVirtualMemory syscall in ntdll.dll.
EXTERN sysAddrNtCreateThreadEx:QWORD                ; The actual address of the NtCreateThreadEx syscall in ntdll.dll.
EXTERN sysAddrNtWaitForSingleObject:QWORD           ; The actual address of the NtWaitForSingleObject syscall in ntdll.dll.


.CODE  ; Start the code section

NtAllocateVirtualMemory PROC
    mov r10, rcx                                    ; Move the contents of rcx to r10. This is necessary because the syscall instruction in 64-bit Windows expects the parameters to be in the r10 and rdx registers.
    mov eax, 18h                                    ; Move the syscall number into the eax register.
    jmp QWORD PTR [sysAddrNtAllocateVirtualMemory]  ; Jump to the actual syscall.
NtAllocateVirtualMemory ENDP                     	; End of the procedure.


TEST_NtWriteVirtualMemory PROC
    mov r10, rcx
    mov eax, 3Ah
    jmp QWORD PTR [sysAddrNtWriteVirtualMemory]
TEST_NtWriteVirtualMemory ENDP


NtCreateThreadEx PROC
    mov r10, rcx
    mov eax, 0C9h
    jmp QWORD PTR [sysAddrNtCreateThreadEx]
NtCreateThreadEx ENDP


NtWaitForSingleObject PROC
    mov r10, rcx
    mov eax, 4
    jmp QWORD PTR [sysAddrNtWaitForSingleObject]
NtWaitForSingleObject ENDP

END