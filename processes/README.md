# Process Injection

🔍 Contenido del Repositorio

| Carpeta | Descripción |
|---|---|
| [**hollowing**](./hollowing) | **Process Hollowing**: ejemplo y análisis de la técnica que crea un proceso legítimo en suspensión y reemplaza su código en memoria por otro payload. <br>Incluye parsing de PE, manejo de contexto de hilos y reubicación básica. |
| [**thread_hijacking**](./thread_hijacking) | **Thread Hijacking / APC / Hijack Threads**: técnicas para redirigir hilos existentes (SuspendThread / SetThreadContext / QueueUserAPC / remote APC) y ejecutar código en el contexto de otro proceso. |
                               |

---

## Guía de Uso

Cada subcarpeta contiene un script `setup.bat` que **prepara las variables de entorno para MSVC** (Visual Studio) y, a continuación, invoca el *makefile* asociado para compilar los ejemplos.

**Uso básico** (desde `cmd.exe`):

```bat
cd <subcarpeta>/setup.bat
```