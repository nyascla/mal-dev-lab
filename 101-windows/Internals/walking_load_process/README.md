# Flujo de Creación de un Proceso en Windows

## 1. Espacio de Usuario (El Shell del Usuario)

1. Doble Clic (Acción del Usuario)
    - El usuario hace doble clic en `main.exe`.
2. `Explorer.exe` (El Shell)
    - Recibe el evento y determina qué archivo ejecutar.
3. `ShellExecuteExW` (en `shell32.dll`)
    - Función de alto nivel que gestiona la ejecución (incluyendo `UAC` y asociaciones de archivos).
4. `CreateProcessW` (en `kernel32.dll`)
    - La función API que prepara el entorno para el nuevo proceso.
5. `NtCreateUserProcess` (en `ntdll.dll`)
    - La syscall de bajo nivel que prepara la transición al modo kernel.
---

## 2. Espacio de Kernel (El Núcleo del SO)

1. `NtCreateUserProcess` (Lado Kernel)
    - El kernel recibe la llamada y comienza la creación del proceso.
2. `PspAllocateProcess`
    - Crea el objeto `EPROCESS` (la estructura principal del kernel para un proceso).
3. `MmCreateAddressSpace`
    - Crea el Espacio de Direcciones Virtual (`VAS`) privado para el nuevo proceso.
4. `NtCreateSection`
    - Crea un "Section Object" (un "plano") a partir del archivo `main.exe` en disco.
5. `NtMapViewOfSection`
    - Mapea el "plano" del `main.exe` en el `VAS`.
6. `NtMapViewOfSection` (de nuevo)
    - Mapea `ntdll.dll` (el cargador) en el `VAS`.
7. `PspCreateThread`
    - Crea el hilo principal del proceso (el objeto `ETHREAD`).
8. `KiInitializeContextThread`
    - Configura el contexto del hilo para que su primera instrucción (`RIP`) apunte al cargador.
---

## 3. Espacio de Usuario (El Nuevo Proceso)

1. `LdrInitializeThunk` (en `ntdll.dll`)
    - La primera instrucción que se ejecuta en el nuevo proceso. Llama al cargador.
2. `LdrpInitialize`
    - El cargador principal. Lee las cabeceras PE del `main.exe`.
3. `LdrpLoadDll` *VER NOTAS EN: [walking_load_dll](../walking_load_dll/)*
    - Lee la Tabla de Importación (`.idata`) y mapea recursivamente todas las DLLs dependientes (como `kernel32.dll`, `user32.dll`, etc.).
4. `LdrpHandleRelocations` (ejecutado en bucle)
    - Si `ASLR` movió una DLL, esta función "parchea" el código de la DLL (usando la sección `.reloc`) para arreglar las direcciones de memoria.
5. `LdrpRunInitializeRoutines` (ejecutado en bucle)
    - Llama a la función `DllMain` de cada DLL que acaba de cargar (con `DLL_PROCESS_ATTACH`).
6. (Salto al Punto de Entrada)
    - El cargador finaliza y salta a la `AddressOfEntryPoint` del `main.exe`, que finalmente llama a tu función `main()`.