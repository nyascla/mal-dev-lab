
# Mingw32

```bash
x86_64-w64-mingw32-gcc --version
```

## Template

```makefile
# ==========================
# Makefile para x86_64-w64-mingw32-gcc
# ==========================

# Directorio de salida
BIN_DIR = bin
EXE     = $(BIN_DIR)/main.exe
DLL     = $(BIN_DIR)/dll.dll
DLL_LIB = $(BIN_DIR)/libdll.a   # GCC genera .a como import library

# Compilador y flags
CC      = x86_64-w64-mingw32-gcc
CFLAGS  = -Wall -Wextra -O2
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
	@mkdir -p $(BIN_DIR)

# Compilar DLL y generar import library
$(DLL): $(SRC_DLL) | $(BIN_DIR)
	@echo "Compilando DLL para Windows (GCC)..."
	$(CC) $(CFLAGS) -shared -o $(DLL) $(SRC_DLL) -Wl,--out-implib=$(DLL_LIB)

# Compilar ejecutable enlazando la import library
$(EXE): $(SRC_MAIN) $(DLL) | $(BIN_DIR)
	@echo "Compilando main.exe para Windows (GCC)..."
	$(CC) $(CFLAGS) $(SRC_MAIN) $(DLL_LIB) -o $(EXE)

# Limpiar binarios
clean:
	@echo "Limpiando..."
	-rm -f $(EXE) $(DLL) $(DLL_LIB) $(BIN_DIR)/*.o

# Ejecutar con wine (Linux/macOS)
run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	wine $(EXE)

.PHONY: all clean run

```