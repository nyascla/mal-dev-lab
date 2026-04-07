# Windows Code Injection

El objetivo es ejecutar codigo malicoso en la sistema vitima
- infectar con c2
- dumpear credenciales
- generar persistencia
- otros

soltar un .exe es muy ruidoso por lo que conviene intentrar ejecutar el codigo en el contexto deun proceso legitimo
para mezclar las accioens maliciosas con legitimas y ser mas dificil de detectar por parte de un edr

> para cada tecnica por los ioc que genera

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

``` css
Code Injection
│
├── Local code injection
│   ├── Stack/Heap injection
│   ├── ROP
│   └── eval() abuse
│
└── Process Injection
    ├── DLL Injection
    ├── Shellcode Injection
    ├── Process Hollowing
    ├── APC Injection
    └── Early Bird Injection

```

- Module Stomping
- Reflective DLL Injection
- Early Bird APC
- Entry Point Injection
- Thread Hijacking
- COM Hijacking
- WMI Event Subscription
- DLL Hijacking

- `APC Injection ` 
  Ejecución de código en el contexto de un hilo existente mediante el uso de Asynchronous Procedure Calls (APC), aprovechando el mecanismo legítimo del sistema operativo cuando el hilo entra en estado alertable.

- `Atom Bombing` 
  Técnica que abusa de la tabla global de átomos de Windows para almacenar referencias a código y provocar su ejecución en un proceso remoto sin necesidad de escribir directamente memoria ejecutable.

- `DLL Hijacking`  
  Manipulación del orden de búsqueda de bibliotecas dinámicas para forzar a un proceso a cargar una DLL maliciosa en lugar de una legítima durante su inicialización o ejecución.

- `DLL Injection`  
  Inserción forzada de una biblioteca dinámica dentro del espacio de memoria de un proceso objetivo, permitiendo la ejecución de código arbitrario dentro de su contexto.

- `Process Hollowing`  
  Creación de un proceso legítimo en estado suspendido cuya imagen en memoria es reemplazada total o parcialmente por código controlado, manteniendo la apariencia externa del proceso original.

- `Reflective Injection`  
  Carga de una biblioteca dinámica directamente desde memoria sin utilizar el cargador estándar del sistema operativo, evitando el uso de `LoadLibrary` y artefactos en disco.

- `Shellcode Injection`  
  Escritura y ejecución directa de código máquina (shellcode) dentro del espacio de memoria de un proceso, sin necesidad de bibliotecas ni estructuras de alto nivel.

- `Thread Hijacking`  
  Técnica que reutiliza un hilo existente modificando su contexto de ejecución para ejecutar código inyectado, evitando la creación de nuevos hilos y reduciendo la visibilidad.
