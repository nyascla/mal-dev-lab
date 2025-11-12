# DLL proxying / API hooking

Un .def le dice al enlazador (link.exe) qué símbolos (funciones, variables, etc.) deben hacerse públicos en la DLL.


archivo .def que exporte exactamente las mismas funciones que la DLL original


```
LIBRARY "user32.dll"
EXPORTS
    ; HOOK: función implementada en TU código fuente
    MessageBoxA = malicious.MessageBoxA_Hook

    ; REEXPORT: funciones de la DLL original (renombrada)
    MessageBoxW     = user32_real.MessageBoxW     @101
    CreateWindowExA = user32_real.CreateWindowExA @50
```

para la maliciosa hay que unsar el nombre del fichero .c que vamos a compilar
para el resto hay que usar el nombre que tendra la dll original en el sistema victima
## @ 
- Es un número entero que identifica una función exportada en lugar de su nombre.
- Algunos programas (especialmente antiguos o de sistema) cargan funciones por ordinal, no por nombre.
- Si un programa carga RegisterClassW con ordinal @201, tu DLL maliciosa debe exportarla con el mismo ordinal, o fallará.

```
cl /LD mydll.c mydll.def
```

# En Visual Studio (cl.exe)
cl malicious.cpp /link /DEF:proxy.def /DLL /OUT:malicious.dll

```
dumpbin /exports C:\Windows\System32\version.dll
```