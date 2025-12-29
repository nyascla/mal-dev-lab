# Windows Internals

- [Debugging Windows Internals with x64dbg!](https://www.youtube.com/watch?v=AKcADaAaOT8)
- [Windows Internals Crash Course](https://www.youtube.com/watch?v=I_nJltUokE0&t=2850s)

windows crea un proceso

recorremos el nuevo proveso

```
Proceso
 └── PEB
      └── LDR
           └── Módulos

Hilo
 └── TEB
      ├── Stack
      ├── TLS
      ├── ClientId
      └── → PEB

```