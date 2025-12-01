# Flujo de Carga de DLLs en Windows

## 1. Carga de la DLL (La llamada a `LoadLibrary`)

Esta secuencia describe lo que ocurre cuando tu código llama a `LoadLibrary("milib.dll")`.

1.  **`LoadLibraryA` / `LoadLibraryW` (en `kernel32.dll`)**
    *   Es la función API que recibe la llamada. Realiza comprobaciones iniciales.

2.  **`LdrLoadDll` (en `ntdll.dll`)**
    *   Esta es la función principal del cargador. Comprueba (en el `PEB`) si la DLL ya está cargada. Si no lo está, continúa.

3.  **`LdrpSearchPath` (en `ntdll.dll`)**
    *   Busca el archivo `.dll` en el disco siguiendo el orden de búsqueda (Directorio del EXE, System32, PATH, etc.).

4.  **`NtCreateSection` (Syscall al Kernel)**
    *   Crea un "Section Object" (un "plano" del archivo) en el kernel.

5.  **`NtMapViewOfSection` (Syscall al Kernel)**
    *   Mapea el plano de la DLL en el Espacio de Direcciones Virtual (`VAS`) del proceso.

6.  **`LdrpHandleRelocations` (en `ntdll.dll`)**
    *   Si `ASLR` movió la DLL a una dirección aleatoria, esta función "parchea" el código de la DLL (usando la sección `.reloc`) para arreglar las direcciones absolutas.

7.  **`LdrpLoadDll` (Recursivo)**
    *   El cargador inspecciona la tabla `.idata` de `milib.dll` y se llama a sí mismo para cargar las dependencias (ej. `user32.dll`).

8.  **`LdrpRunInitializeRoutines` (en `ntdll.dll`)**
    *   Llama a la función `DllMain` de `milib.dll` (y de sus dependencias) con el motivo `DLL_PROCESS_ATTACH`.

9.  **(Retorno)**
    *   El cargador devuelve el handle (la `ImageBase` real donde se cargó la DLL) a la función `LoadLibraryA`, que te la devuelve a ti.

---

## 2. Búsqueda de la Función (La llamada a `GetProcAddress`)

Esta secuencia ocurre después de `LoadLibrary`, cuando llamas a `GetProcAddress(hDll, "MiFuncion")`.

1.  **`GetProcAddress` (en `kernel32.dll`)**
    *   La función API que recibe la llamada.

2.  **`LdrGetProcedureAddress` (en `ntdll.dll`)**
    *   La función real del cargador que realiza la búsqueda.

3.  **(Parseo de la EAT)**
    *   `LdrGetProcedureAddress` localiza la Tabla de Exportación (`EAT`) (sección `.edata`) de la DLL.
    *   Busca el string `"MiFuncion"` en la lista de nombres de la `EAT` para encontrar su dirección (`RVA`).

4.  **(Retorno)**
    *   La función calcula la dirección absoluta (`ImageBase` + `RVA`) y devuelve ese puntero de función a tu código.