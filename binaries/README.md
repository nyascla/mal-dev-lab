## ASLR

Cuando clono el ejecutable me cambia el AddressOfEntryPoint

## Memoria:
AddressOfEntryPoint - RVA del primer byte que se ejecuta al iniciar el programa
BaseOfCode - RVA donde empieza la sección de código ejecutable (.text).
BaseOfData - RVA donde empieza la sección de datos inicializados
ImageBase - Dirección virtual preferida donde se carga el PE en memoria
VirtualAddress - Inicio de la seccion en memoria

## Disco:
PointerToRawData: Inicio de seccion en disco

> Tener en cuenta que por ejemplo en C el entry point es el crt startup y no main (en IDA start)

EntryPoint:
- Memoria: ImageBase + AddressOfEntryPoint
- Disco: (AddressOfEntryPoint - VirtualAddress) + PointerToRawData

---

## modificar el codigo del entry point para que contenga mi shellcode

Disco, calcular el offset al densde el inicio de la seccion al entry point 


(00001131 - 00001000) + 00000400 = 531

![alt text](image.png)

la primera aproximacion me da un error 0xC0000005 el ejecutar con doble click y un ERROR_SEM_NOT_FOUND des x32dbg

Mi primera teoria es que al alargar la seccion .text al copiarla en memoria pisa algo de otra seccion 

ahora voy a probar a anyadir el codigo de la shellcode y borrar casa que ya estaban para no aumentar el tam de .text

ahora ya puedo ejecutar mi codigo, aunque peta a mitad ejecucion

lo que esta pasando es que las etiquetas que utiliza como variables no estan funcionando bien

Claro los permisos de .text son ER no puede escribir en esa direcciones

puedo hacer el mismo codigo sin escrituras en memoria?

---
