# Secuentro de Contexto de Activacion

Objetivo suministrar a un proceso confiable un contexto de activacion malicioso

![alt text](image-2.png)

PERO el contexto de activacion es inmutable

3 lugares donde se busca el contexto cuando el SO solicita la carga de una dll

va mirando si tien un contexto de activacion con una redireccion a la dll que quiere cargar

1. TEB.ActivationStack (del hilo que ha salicidado la carga de la dll)
    - un punto a una pila de contextos de activacion
2. PEB.ActivationContextData
    - un puntero a un contexto de activacion (Main Activation Context)
    - el primer contexto de activacion creado por `csrss.exe`
3. PEB.SystemDefaultActivationContextData
    - este esta siempre haya o no haya un manifest en el binario principal

si modificamos la direccion a la que apunta `PEB.ActivationContextData` habremenos hecho un hijack sobre el contexto de activacion

haremos que el puntero apunte a un contexto de activacion donde la redireccion a la dll sea una de nuestra conveniencia

> nota: la ruta WinSxS esta contrada por la cuenta trusted installer, por lo que para escribit en esa ruta deberiamos escalar privilegios por encima de system


ejemplo de un manifest secuentado, notar `loadFrom`

escribimos en memoria el nuevo manifaest y cambiamos el puntero PEB.ActivationContextData

![alt text](image-4.png)

minuto explicacion hjijack

https://youtu.be/qu4fXWKjabY?t=3246