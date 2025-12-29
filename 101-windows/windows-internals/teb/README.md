# TEB (Thread Environment Block)

El TEB (Thread Environment Block) es una estructura en memoria en modo usuario, una por hilo, creada por el kernel al crear el thread.

Cada hilo tiene su propio TEB, y el puntero al TEB está siempre accesible mediante un registro de segmento.

| Arquitectura | Registro | Offset      |
| ------------ | -------- | ----------- |
| x86 (32-bit) | `FS`     | `FS:[0x18]` |
| x64          | `GS`     | `GS:[0x30]` |

- Enumerar todos los TEBs del proceso
- Leer TLS slots
- Detectar hooks en TEB
- Comparar PEB->BeingDebugged vs flags en TEB
- Anti-debugging real (NtGlobalFlag, heap flags, etc.)\

## Enumerar todos los TEBs del proceso

Obtener el TEB del hilo actual, 
`GS:[0x30]`: GS es contexto de CPU

```
CPU core
 └── ejecuta hilo A → GS = TEB_A
 └── ejecuta hilo B → GS = TEB_B
```

``` c
return __readgsqword(0x30); // GS:[0x30] → TEB
```

Para obtener todos los TEB de un proceso `NtQueryInformationThread`

1. Enumeras todos los threads del proceso
2. Abres cada thread (OpenThread)
3. Llamas a: `NtQueryInformationThread`
4. Obtienes: THREAD_BASIC_INFORMATION.TebBaseAddress


