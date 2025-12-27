# Windows Code Injection

## code injection vs process injection

- `code`: Introducir código arbitrario en un contexto de ejecución que no estaba previsto.
    - Shellcode en el stack (buffer overflow)
    - ROP chains
    - DLL hijacking (parcialmente)
    - JIT spraying
    - SQL injection → ejecución indirecta
    - eval() abuse
    - Macro injection
- `process`: Ejecutar código dentro del espacio de direcciones de OTRO proceso.
    - CreateRemoteThread
    - NtCreateThreadEx
    - Process Hollowing
    - Process Doppelgänging
    - Reflective DLL Injection
    - APC Injection
    - Thread Hijacking

Toda process injection es code injection

```
Code Injection
│
├── Local code injection
│   ├── Stack/Heap injection
│   ├── ROP
│   └── Self-modifying code
│
└── Process Injection
    ├── DLL Injection
    ├── Shellcode Injection
    ├── Process Hollowing
    ├── APC Injection
    └── Early Bird Injection

```