# DLL proxying / API hooking

El DLL proxying es una técnica que permite interponer una biblioteca dinámica maliciosa entre una aplicación y la DLL legítima que esta espera cargar.

la DLL proxy reexporta ciertas funciones apuntando directamente a la DLL original. Un ejemplo simplificado de una tabla de exportaciones modificada sería:

```
Export Address Table -- Ordinal Base 1
	[   0] +base[   1] 13e4 Export RVA
	[   1] +base[   2] d05a Forwarder RVA -- real-old.FuncB
	[   2] +base[   3] d06f Forwarder RVA -- real-old.FuncC
```

## El fichero `.def`

Un fichero `.def` (de Module Definition File) es un archivo de texto que se utiliza en desarrollo de aplicaciones Windows para definir explícitamente cómo una DLL expone sus funciones, datos y recursos.

```bash
x86_64-w64-mingw32-gcc -shared -o bin/malicious.dll dll-malicious.c proxy.def -s`
```

Creando el contenido de un .def que reexporta las funciones de `real.dll`

``` python
import pefile

dll = pefile.PE('./real.dll')

print("EXPORTS")
for export in dll.DIRECTORY_ENTRY_EXPORT.symbols:
    if export.name:
        print('{}=real-old.{} @{}'.format(export.name.decode(), export.name.decode(), export.ordinal))
```

> NOTA: el campo `@` 
> - (ordinal) Es un número entero que identifica una función exportada en lugar de su nombre.


## Salida ejecucion de la Demo

```
➜  dll-proxying git:(main) ✗ wine bin/main.exe
[DLL hijacked] Process Attached
[DLL real] Process Attached
[MAIN] Hello from main!
[DLL hijacked] FuncA_Hook ejecutada
[DLL hijacked] Llamando a FuncA original...
[DLL real] func FuncA
[DLL real] func FuncB
[DLL real] func FuncC
[MAIN] Goodbye from main!
[DLL real] Process Detached
[DLL hijacked] Process Detached
```