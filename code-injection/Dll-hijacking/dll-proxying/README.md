# DLL proxying / API hooking


## `.def`

Un .def le dice al enlazador (link.exe) qué símbolos (funciones, variables, etc.) deben hacerse públicos en la DLL.

archivo .def que exporte exactamente las mismas funciones que la DLL original

### @ 
- Es un número entero que identifica una función exportada en lugar de su nombre.
- Algunos programas (especialmente antiguos o de sistema) cargan funciones por ordinal, no por nombre.
- Si un programa carga RegisterClassW con ordinal @201, tu DLL maliciosa debe exportarla con el mismo ordinal, o fallará.
