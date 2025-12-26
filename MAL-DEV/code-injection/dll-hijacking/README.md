# DLL Hijacking

https://hijacklibs.net/

## Objetivos

Conseguir que el loader de Windows cargue una librería dinámica bajo nuestro control mediante la explotación del orden de carga o configuraciones del sistema.

## Orden de Carga de DLLs en Windows

1. Directorio desde el cual se cargó la aplicación
2. C:\Windows\System32
3. C:\Windows\System  
4. C:\Windows
5. Directorio actual de trabajo (Current Working Directory)
6. Directorios en la variable PATH del sistema
7. Directorios en la variable PATH del usuario

## KnownDLLs - Limitación Importante

DLLs listadas aquí se cargan exclusivamente desde System32.

```
Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\KnownDLLs
```
## Discovering (Process Monitor)

Querys de ProcMon

| Column    | Relation  | Value         | Action    |
|---        |---        |---            |---        |
| Operation | is        | CreateFile    | Include   |
| Result    | is        | NAME NOTFOUND | Include   |
| Path      | ends with | .dll          | Include   |

## Weaponization

> DLL Side-Loading + Proxy

- Mecanismo: Colocar DLL maliciosa en el mismo directorio que el ejecutable
- Característica: La DLL maliciosa actúa como proxy, redirigiendo llamadas a la DLL legítima

[Dll Proxying](./dll-proxying)


## Process Deadlocking

No realizar muchas operaciones en DLLMain

![alt text](./img/image-1.png)

## Hijacking Using COM

> Falta desarrollar