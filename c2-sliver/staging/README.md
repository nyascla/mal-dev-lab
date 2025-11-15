# Staging system

Sliver está diseñado principalmente como `payload de etapa 2 (stager)`.
Ver documentación oficial: https://sliver.sh/docs?name=Stagers

Como cargar el payload principal en memoria


Stage 0 (opcional): shellcode, comandos

Stage 1: c/rust, cargar el payload principal en memoria y ejecutarlo
- conexion red
- encriptado
persistencia favorita dll hijacking, si conseguimos hacer que els stage 1 sea una dll este es una buen sistema de persistencia
- no run keys
se adjunta a un programa que este siempre corriendo o se ejecute al inicio

Stage 2: dll/dialect/share object, el payload principal
puede no ser persistente y que solo sea persistente el stage 1
otra opcion image file execution options
ficheros lmk
extensiones de chrome

persistance puede ser triqui, si la maquina es re explotable alomejor conviene no tener persistencia para ser mas dificil de detectar