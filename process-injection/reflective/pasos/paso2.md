# Paso-2 (preparativos)
- Tener metodo ReflectiveLoader() que revuelva:
    - Su base addres
    - Obtenga informacion de sus headers (no se cual :/)
    - Obtenga las funciones:
        - LoadLibraryA
        - GetProcAddress 
        - VirtualAlloc

## Paso-3 (loading de la dll)
- Desde una dll copiar el PE de una dll y arreglar las relocaciones y arrancar la dll 