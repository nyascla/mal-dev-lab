### Syscalls usando la API estándar de Windows
- Carpeta: [win32-api](./win32-api/)  
- Descripción: PoCs que utilizan funciones de la WinAPI que internamente invocan syscalls, manteniendo compatibilidad y reduciendo la detección.

### Syscalls usando la API nativa de Windows
- Carpeta: [native-api](./native-api/)  
- Descripción: PoCs que llaman directamente a las funciones `Nt*` de la API nativa, evitando la capa de WinAPI para evadir hooks y análisis.

### Syscalls directamente en ensamblador
- Carpeta: [direct-syscalls](./direct-syscalls/)  
- Descripción: PoCs que ejecutan llamadas al kernel directamente desde ASM, sin pasar por ninguna capa de API.

### Syscalls con manipulación del call stack
- Carpeta: [indirect-syscalls](./indirect-syscalls/)  
- Descripción: PoCs que realizan llamadas directas al kernel desde ASM **mejorando o manipulando el call stack** para dificultar depuración y evasión de EDR.
