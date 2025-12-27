# TEB (Thread Environment Block)

El TEB (Thread Environment Block) es una estructura en memoria en modo usuario, una por hilo, creada por el kernel al crear el thread.

Cada hilo tiene su propio TEB, y el puntero al TEB está siempre accesible mediante un registro de segmento.

| Arquitectura | Registro | Offset      |
| ------------ | -------- | ----------- |
| x86 (32-bit) | `FS`     | `FS:[0x18]` |
| x64          | `GS`     | `GS:[0x30]` |

