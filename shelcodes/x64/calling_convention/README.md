# Microsoft x64 calling convention

## Alineación de Pila

RSP debe ser múltiplo de 16 (RSP mod 16 == 0)

## Argumentos

- Los **primeros 4 argumentos** se pasan en registros:
	1. **RCX** → primer argumento
	2. **RDX** → segundo argumento
	3. **R8** → tercer argumento
	4. **R9** → cuarto argumento
- Argumentos adicionales se pasan **en la pila**, de derecha a izquierda.


## Shadow space

- Antes de cada `call`, el **caller** debe reservar **32 bytes en la pila** (4 × 8 bytes) como “shadow space”.
- Este espacio es usado por la función llamada si necesita guardar los registros RCX, RDX, R8 o R9.
- No contiene los argumentos, solo es obligatorio reservarlo:

```bash
sub rsp, 32   ; reservar shadow space
call my_function
add rsp, 32   ; restaurar pila
```


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