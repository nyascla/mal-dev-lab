# Basicos

## Registros

| Registro 64-bit | 32-bit | 16-bit | 8-bit alto/bajo | Uso típico                                                          |
| --------------- | ------ | ------ | --------------- | ------------------------------------------------------------------- |
| RAX             | EAX    | AX     | AH/AL           | Acumulador, operaciones aritméticas, retorno de funciones           |
| RBX             | EBX    | BX     | BH/BL           | Base, registro calificador, preservado por la convención de llamada |
| RCX             | ECX    | CX     | CH/CL           | Contador, primer argumento de funciones Windows x64                 |
| RDX             | EDX    | DX     | DH/DL           | Datos, segundo argumento de funciones Windows x64                   |
| RSI             | ESI    | SI     | —               | Fuente de datos, tercer argumento (RDI/RSI)                         |
| RDI             | EDI    | DI     | —               | Destino de datos, cuarto argumento (RCX/RDX en Windows x64)         |
| RBP             | EBP    | BP     | —               | Base pointer / frame pointer, preservado                            |
| RSP             | ESP    | SP     | —               | Stack pointer, siempre alineado a 16 bytes antes de `call`          |
| R8              | R8D    | R8W    | R8B             | 5º argumento de funciones Windows x64                               |
| R9              | R9D    | R9W    | R9B             | 6º argumento de funciones Windows x64                               |
| R10             | R10D   | R10W   | R10B            | Uso general, volatile (caller-saved)                                |
| R11             | R11D   | R11W   | R11B            | Uso general, volatile                                               |
| R12             | R12D   | R12W   | R12B            | Uso general, callee-saved                                           |
| R13             | R13D   | R13W   | R13B            | Uso general, callee-saved                                           |
| R14             | R14D   | R14W   | R14B            | Uso general, callee-saved                                           |
| R15             | R15D   | R15W   | R15B            | Uso general, callee-saved                                           |






