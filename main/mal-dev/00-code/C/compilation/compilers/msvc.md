# MSVC

## Compilador [cl]

- ``/nologo``: no muestren el “banner” inicial con la versión del compilador/enlazador
- ``/W3``: en MSVC controla el nivel de advertencias (warnings) que el compilador muestra
- ``/MDd``: usar la versión debug de la CRT dinámica (en vez de /MD).
- ``/Zi``: generar información de depuración (PDB).
- ``/Od``: desactivar optimizaciones (mejora la depuración).
- ``/RTC1``: comprobaciones en tiempo de ejecución (desbordamientos de pila, uso de variables - no inicializadas) — útil en debug.
- ``/I include``: cl le dice al compilador de MSVC que agregue un directorio al include search path, es decir, a la lista de rutas donde buscará los archivos de cabecera (#include "..." o #include <...>).
- ``/c``: Compila solo hasta generar el archivo objeto (.obj), pero no enlaces.

```
cl /nologo /W3 /MDd /Zi /Od /RTC1 /I include /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
```

## Linker [link]

- ``/DEBUG``: provoca que el linker cree un fichero .pdb (Program Database) y escriba en el PE (EXE/DLL) una entrada IMAGE_DEBUG_DIRECTORY que apunta a ese PDB.
- ``/DYNAMICBASE``: marca el binario como “ASLR-compatible” [activado por defecto]
- ``/NXCOMPAT``: indica que el binario soporta DEP [activado por defecto]

```
/link /DEBUG /OUT:bin\main.exe build\main.obj
```

## Template

```makefile
# ==========================
# Makefile para MSVC
# ==========================

# Directorio de salida
BIN_DIR = bin
EXE     = $(BIN_DIR)/main.exe
DLL     = $(BIN_DIR)/dll.dll
DLL_LIB = $(BIN_DIR)/dll.lib

# Compilador y flags
CC      = cl
CFLAGS  = /nologo /W3 /O2 /EHsc
LDFLAGS = 

# Fuentes
SRC_MAIN = main.c suma.c
SRC_DLL  = dll.c

# ------------------------
# Targets
# ------------------------
all: $(BIN_DIR) $(DLL) $(EXE)

# Crear directorio de salida
$(BIN_DIR):
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Compilar DLL
$(DLL): $(SRC_DLL) | $(BIN_DIR)
	@echo Compilando DLL para Windows (MSVC)...
	$(CC) $(CFLAGS) /LD $(SRC_DLL) /Fe:$(DLL) /Fo:$(BIN_DIR)/dll.obj

# Compilar ejecutable
$(EXE): $(SRC_MAIN) $(DLL) | $(BIN_DIR)
	@echo Compilando main.exe (MSVC)...
	$(CC) $(CFLAGS) $(SRC_MAIN) /Fe:$(EXE) $(DLL_LIB)

# Limpiar binarios
clean:
	@echo Limpiando...
	-if exist $(EXE) del $(EXE)
	-if exist $(DLL) del $(DLL)
	-if exist $(DLL_LIB) del $(DLL_LIB)
	-if exist $(BIN_DIR)\*.obj del $(BIN_DIR)\*.obj

.PHONY: all clean
```