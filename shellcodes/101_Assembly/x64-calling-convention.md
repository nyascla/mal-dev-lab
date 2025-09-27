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