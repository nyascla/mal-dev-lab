``` scss
PEB
 └── [0x0C] -> PEB_LDR_DATA
       └── [0x0C] -> InLoadOrderModuleList (LIST_ENTRY)
               └── _LDR_DATA_TABLE_ENTRY
                     ├── [0x30] -> DllBase (base del módulo)
                     └── [0x44] -> BaseDllName (nombre del módulo)
```


## _PEB
``` c
typedef struct _PEB {
    /* 0x000 */ BYTE   Reserved1[2];              // Reservado
    /* 0x002 */ BYTE   BeingDebugged;             // Flag: 1 si el proceso está bajo depuración
    /* 0x003 */ BYTE   Reserved2[1];              // Reservado
    /* 0x004 */ PVOID  Reserved3[2];              // Reservado
    /* 0x00C */ PPEB_LDR_DATA Ldr;                // Estructura de cargadores (listas de módulos)
    /* 0x010 */ PRTL_USER_PROCESS_PARAMETERS ProcessParameters; // Parámetros del proceso (línea de comandos, entorno, etc.)
    /* 0x014 */ PVOID  Reserved4[3];              // Reservado
    /* 0x020 */ PVOID  AtlThunkSListPtr;          // Interno ATL thunk list
    /* 0x024 */ PVOID  Reserved5;                 // Reservado
    /* 0x028 */ ULONG  Reserved6;                 // Reservado
    /* 0x02C */ PVOID  Reserved7;                 // Reservado
    /* 0x030 */ ULONG  Reserved8;                 // Reservado
    /* 0x034 */ ULONG  AtlThunkSListPtr32;        // Versión 32-bit de AtlThunkSListPtr (WOW64)
    /* 0x038 */ PVOID  Reserved9[45];             // Reservado
    /* 0x0EC */ BYTE   Reserved10[96];            // Reservado
    /* 0x14C */ PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine; // Rutina llamada tras la inicialización del proceso
    /* 0x150 */ BYTE   Reserved11[128];           // Reservado
    /* 0x1D0 */ PVOID  Reserved12[1];             // Reservado
    /* 0x1D4 */ ULONG  SessionId;                 // ID de sesión (Terminal Services)
} PEB, *PPEB;
```

## _PEB_LDR_DATA
``` c
typedef struct _PEB_LDR_DATA {
    /* 00h */ ULONG Length;                 // Tamaño de esta estructura
    /* 04h */ BOOLEAN Initialized;          // TRUE si está inicializada
    /* 05h */ BYTE   Reserved1[3];          // Alineación

    /* 08h */ PVOID SsHandle;               // Handle de la sesión

    /* 0Ch */ LIST_ENTRY InLoadOrderModuleList;  
    // Lista doblemente enlazada de LDR_DATA_TABLE_ENTRY
    // Ordenados por carga

    /* 14h */ LIST_ENTRY InMemoryOrderModuleList; 
    // Lista doblemente enlazada de LDR_DATA_TABLE_ENTRY
    // Ordenados por direcciones de memoria

    /* 1Ch */ LIST_ENTRY InInitializationOrderModuleList; 
    // Lista doblemente enlazada de LDR_DATA_TABLE_ENTRY
    // Ordenados por inicialización

    /* 24h */ PVOID EntryInProgress;        // DLL que se está cargando actualmente
    /* 28h */ BOOLEAN ShutdownInProgress;   // TRUE si se está descargando
    /* 29h */ PVOID ShutdownThreadId;       // ID del hilo que descarga
} PEB_LDR_DATA, *PPEB_LDR_DATA;

```

## _LIST_ENTRY
``` c
typedef struct _LIST_ENTRY {
    /* 0x00 */ struct _LIST_ENTRY *Flink;  // Forward Link → puntero al siguiente elemento en la lista
    /* 0x04 */ struct _LIST_ENTRY *Blink;  // Backward Link → puntero al elemento anterior en la lista
} LIST_ENTRY, *PLIST_ENTRY;
```

## _LDR_DATA_TABLE_ENTRY
``` c
typedef struct _LDR_DATA_TABLE_ENTRY {
    /* 0x000 */ LIST_ENTRY InLoadOrderLinks;          // Siguiente/previo módulo en la lista "LoadOrder"
    /* 0x008 */ LIST_ENTRY InMemoryOrderLinks;        // Lista de módulos en orden de memoria
    /* 0x010 */ LIST_ENTRY InInitializationOrderLinks;// Lista de módulos en orden de inicialización

    /* 0x018 */ PVOID DllBase;                        // Dirección base donde está cargada la DLL
    /* 0x01c */ PVOID EntryPoint;                     // Dirección del entrypoint (DllMain / EntryPoint)
    /* 0x020 */ ULONG SizeOfImage;                    // Tamaño del módulo en memoria

    /* 0x024 */ UNICODE_STRING FullDllName;           // Nombre completo (con ruta), ej: C:\Windows\System32\kernel32.dll
    /* 0x02c */ UNICODE_STRING BaseDllName;           // Nombre corto/base, ej: kernel32.dll

    /* 0x034 */ ULONG Flags;                          // Flags internos de carga
    ...
    
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;
```

## _UNICODE_STRING
``` c
typedef struct _UNICODE_STRING {
    /* 0x00 */ USHORT Length;         // Longitud real de la cadena en bytes (no incluye terminador nulo)
    /* 0x02 */ USHORT MaximumLength;  // Capacidad máxima del buffer en bytes (incluye espacio para terminador nulo)
    /* 0x04 */ PWSTR  Buffer;         // Puntero al buffer de la cadena (UTF-16, NO está null-terminated garantizado)
} UNICODE_STRING, *PUNICODE_STRING;
```