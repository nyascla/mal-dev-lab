| Tipo        | `Type`        | Respaldada por  |
| ----------- | ------------- | --------------- |
| **Private** | `MEM_PRIVATE` | Pagefile / RAM  |
| **Mapped**  | `MEM_MAPPED`  | Archivo mapeado |
| **Image**   | `MEM_IMAGE`   | PE (EXE / DLL)  |

Una región de memoria privada es una región de memoria virtual:
- Reservada y/o comprometida directamente por el proceso
- No respaldada por ningún archivo en disco
- Exclusiva de ese proceso
