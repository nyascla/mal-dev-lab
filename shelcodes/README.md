# Shellcode - x86 & x64

## Tácticas

> Los **objetivos de alto nivel** que persigue el shellcode:

| Táctica | Descripción |
|---------|------------|
| Execution | Ejecutar código en el sistema objetivo. |
| Persistence | Mantener presencia en el sistema a través de código inyectado o persistente. |
| Defense Evasion | Evadir mecanismos de detección como AV, EDR o debugging. |
| Privilege Escalation | Escalar privilegios si el shellcode lo permite. |

---

## Técnicas

> Los **métodos generales** que el shellcode implementa:

| Técnica | Descripción |
|---------|------------|
| Process Injection | Inyección de shellcode en otro proceso para ejecución oculta. |
| Remote Shell | Shellcode que establece un canal de comunicación remoto (TCP/HTTP). |
| Runtime Linking | Resolución dinámica de funciones en memoria para evadir import tables. |
| Import Hashing | Uso de hashes para resolver funciones evitando strings y análisis estático. |

---

## Procedimientos

> Implementaciones concretas

### Import Hashing 
- Carpeta: [hashes](./x86/runtime_linking/hashes)  
- Descripción: 


### Runtime Linking
- Carpeta: [runtime-linking](./x86/runtime_linking/)  
- Descripción: 


### Remote Shell
- Carpeta: [___](./)  
- Descripción: 
