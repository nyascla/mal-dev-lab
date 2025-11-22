## Execution policy bypass

```
powershell -ep bypass -File ".\x64.ps1"
```

## AMSI Bypass - Memory Patching via Reflection

> "El bypass de Matt Graeber"

### Objetivo

Desactivar completamente AMSI en la sesión actual de PowerShell sin tocar un solo byte de amsi.dll, evitando así todas las detecciones basadas en parcheo de memoria.

### Cómo funciona

Cuando PowerShell inicia, la clase privada `System.Management.Automation.AmsiUtils` crea una variable estática llamada `amsiInitFailed`. Si esta variable está en $true, AMSI considera que la inicialización falló y desactiva todos los escaneos durante toda la sesión, aunque amsi.dll siga cargada y perfectamente funcional.

desde un script combinando poweshell y c# utilizaremos getprocaddress loadlibrary y virutalprotect prara cargar amsi.dll en memoria

con la marshall copy tecnic modificareemos el dea eax para que siempre devuelva lo mismo


si la funcion devuelve un hresult cualquier script se puede ejecutar

## AMSI Bypass – Memory Patching

### Objetivo

Hacer que cualquier script PowerShell pase el escaneo de AMSI (Antimalware Scan Interface) sin ser bloqueado por Windows Defender u otros AV/EDR que usen esta interfaz.

### Cómo funciona AMSI

Cuando PowerShell (o cualquier motor de scripting) ejecuta código, antes de interpretarlo llama a la función AmsiScanBuffer() dentro de amsi.dll.
Esta función analiza el buffer y devuelve un HRESULT:

- https://learn.microsoft.com/es-es/windows/win32/api/amsi/nf-amsi-amsiscanbuffer
- https://learn.microsoft.com/es-es/shows/inside/hresult

### Idea del bypass

Modificar en tiempo de ejecución los primeros bytes de AmsiScanBuffer() para que siempre devuelva un valor “limpio” (normalmente 0x80070057 → E_INVALIDARG, que paradójicamente AMSI interpreta como “no es malware” en muchas versiones).
Técnica paso a paso:

1. Cargar amsi.dll (ya está en memoria en cualquier proceso PowerShell).
1. Obtener la dirección de AmsiScanBuffer usando `GetProcAddress`.
1. Cambiar los permisos de esa región de memoria a PAGE_EXECUTE_READWRITE con `VirtualProtect`.
1. Sobreescribir los primeros bytes con un parche pequeño: (bytes: B8 57 00 07 80 C3)

``` nasm
mov eax, 0x80070057   ; E_INVALIDARG → AMSI lo toma como “limpio”
ret                  
```
