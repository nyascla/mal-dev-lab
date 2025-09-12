# Syscalls

## Tácticas

> Segun el objetivo final

| Táctica (TTP)            | Descripción                      | Ejemplo con syscalls                                                 |
| ------------------------ | -------------------------------- | -------------------------------------------------------------------- |
| **Execution**            | Ejecutar código en el sistema    | `NtCreateThreadEx` para ejecutar un hilo en otro proceso             |
| **Persistence**          | Mantener presencia en el sistema | `NtSetValueKey` para modificar el registro y lograr persistencia     |
| **Defense Evasion**      | Evadir detección o protecciones  | `NtQuerySystemInformation` para detectar debugging o AV              |                       |
| **Exfiltration**         | Extraer información              | `NtReadFile` y `NtWriteFile` para copiar datos a un canal controlado |
| **Privilege Escalation** | Elevar privilegios               | `NtAdjustPrivilegesToken` para habilitar privilegios administrativos |


## Técnicas

> Métodos generales que usualmente implementan las syscalls

| Técnica                                | Descripción                                         | Syscall típica                                          |
| -------------------------------------- | --------------------------------------------------- | ------------------------------------------------------- |
| **Process Injection**                  | Inyectar código en otro proceso                     | `NtWriteVirtualMemory`, `NtCreateThreadEx`              |
| **API Hook Evasion / Direct Syscalls** | Evadir hooks de seguridad de API                    | llamadas directas a `Nt*` en vez de WinAPI              |
| **Memory Manipulation**                | Leer/escribir memoria de procesos                   | `NtReadVirtualMemory`, `NtWriteVirtualMemory`           |
| **File Manipulation**                  | Interactuar con archivos sin pasar por API estándar | `NtCreateFile`, `NtReadFile`, `NtWriteFile`             |
| **Thread Execution Hijacking**         | Controlar hilos de otros procesos                   | `NtQueueApcThread`, `NtSuspendThread`, `NtResumeThread` |


## Procedimientos

> Implementaciones concretas

### Syscalls usando la API estándar de Windows
- Carpeta: [win32-api](./win32-api/)  
- Descripción: PoCs que utilizan funciones de la WinAPI que internamente invocan syscalls, manteniendo compatibilidad y reduciendo la detección.

### Syscalls usando la API nativa de Windows
- Carpeta: [native-api](./native-api/)  
- Descripción: PoCs que llaman directamente a las funciones `Nt*` de la API nativa, evitando la capa de WinAPI para evadir hooks y análisis.

### Syscalls directamente en ensamblador
- Carpeta: [direct-syscalls](./direct-syscalls/)  
- Descripción: PoCs que ejecutan llamadas al kernel directamente desde ASM, sin pasar por ninguna capa de API.

### Syscalls con manipulación del call stack
- Carpeta: [indirect-syscalls](./indirect-syscalls/)  
- Descripción: PoCs que realizan llamadas directas al kernel desde ASM **mejorando o manipulando el call stack** para dificultar depuración y evasión de EDR.
