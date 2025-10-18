# C2

implant vs server

pre-exploit vs post-exploit

entre pre y post viven los stagers
Un stager es un pequeño y sigiloso fragmento de código cuyo único propósito es establecer una conexión con el servidor del atacante para descargar y ejecutar un payload mucho más grande y complejo (el "stage").

Es la primera parte de un sistema de entrega de malware en dos etapas.

los stager es mas normal que toquen el disco, el stage principal la idea es que sea solo memoria

## Hacer llegar el payload (sliver implant) al objetivo

Staging system, depende de como se consiga la ejecucion de codigo

Stage 0 (opcional): shellcode, comandos

Stage 1: c/rust, cargar el payload principal en memoria y ejecutarlo
- conexion red
- encriptado

Stage 2: dll/dialect/share object, el payload principal