# Binary Patching 

## Pasos

### 1. Redirigir el Entry Point al Shellcode
    - Buscar un bloque de bytes libre en .text para colocar el shellcode
    - Calcular la nueva dirección del EntryPoint
    - Modificar AddressOfEntryPoint en el encabezado PE para que apunte a la ubicación del shellcode

### 2. Preservar el Flujo de Ejecución Original
    - Al final del shellcode, devolver la ejecución al punto de entrada original
    - Calcular la dirección del punto de entrada original usando:
        - Dirección base del módulo
        - Valor original de AddressOfEntryPoint

#### NOTE: EntryPoint
- ``Memoria``: BaseAddres + AddressOfEntryPoint
- ``Disco``: (AddressOfEntryPoint - VirtualAddress[rva .text memoria]) + PointerToRawData[rva .text disco]