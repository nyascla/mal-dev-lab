# Atom Bombing

Windows tiene una característica llamada Global Atom Table

una memoria compartida legítima.

- Cualquier programa puede guardar un dato (un string) ahí y recibe un identificador - (un número).
- Cualquier otro programa que tenga ese número puede leer el dato.
- Es una función totalmente normal y legítima del sistema operativo para compartir datos simples.

## Paso A: Escribir en el Tablón (GlobalAddAtom)

## Paso B: Obligar a la víctima a recogerlo (APC Injection)

## Paso C: Ejecución (ROP Chain)