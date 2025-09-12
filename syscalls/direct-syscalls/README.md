system calls are needed in Windows to perform the (temporary) transition (CPU switch) from user mode to kernel mode, or to execute tasks initiated in user mode that require temporary access to kernel mode

```
# x64 native tools
# Ensambla
ml64 /c /Fo syscalls.obj syscalls.asm
# Compila
cl /c loader.c
# Linkea
link loader.obj syscalls.obj /SUBSYSTEM:CONSOLE
```
```
# Windows Build
OS Name	Microsoft Windows 11 Pro
Version	10.0.26100 Build 26100
```

## Buscar el System Service Number (SSN) para el "syscall stub"

`mov eax SSN`

En x64dbg
En ntdll.dll
Buscamos la funcion que queremos

Direct syscalls can be detected if an EDR uses Event Tracing for Windows (ETW) or Event Tracing for Windows Threat Intelligence (EtwTi) to check from which memory area the syscall instruction or function return address was executed, or more specifically if the execution was outside of ntdll.dll memory.