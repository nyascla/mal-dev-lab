# Windows Dlls Code Injection

## 🔍 Contenido del Repositorio

| Carpeta | Descripción |
|---------|-------------|
| [**hijacking**](./hijacking) | Estudio de técnicas de **DLL Hijacking** y otros vectores para alterar el flujo de ejecución de un proceso cargando librerías arbitrarias. Incluye ejemplos de detección y mitigación. |
| [**injection**](./injection) | Ejemplos clásicos de **code injection**: técnicas como CreateRemoteThread, WriteProcessMemory, SetWindowsHookEx, etc., para inyectar código o librerías en procesos remotos. |
| [**reflective**](./reflective) | Investigación sobre **Reflective DLL Injection**, una técnica avanzada que permite cargar DLLs directamente en memoria sin tocar el disco, comúnmente usada en pruebas de penetración y malware. |

---

## Guía de Uso

Cada subcarpeta contiene un script `setup.bat` que **prepara las variables de entorno para MSVC** (Visual Studio) y, a continuación, invoca el *makefile* asociado para compilar los ejemplos.

**Uso básico** (desde `cmd.exe`):

```bat
cd <subcarpeta>/setup.bat
```
