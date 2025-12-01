# =======================================
# Makefile para Clang (cross-compiling a Windows)
# =======================================

ifeq ($(OS),Windows_NT)
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE1)
else
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE1)
endif

# Directorio de salida
BIN_DIR = bin
SRC_DIR = src

# Archivos generados
EXE1 = $(BIN_DIR)/main-loader-noaslr.exe
EXE2 = $(BIN_DIR)/main-loader.exe
DLL  = $(BIN_DIR)/dllmock.dll

# Compilador y flags
CC     = clang
CFLAGS = -Wall -s

# Fuentes
SRC_EXE1 = $(SRC_DIR)/main-loader-noaslr.c
SRC_EXE2 = $(SRC_DIR)/main-loader.c
SRC_DLL  = $(SRC_DIR)/dllmock.c

# =======================================
# Targets principales
# =======================================
all: $(EXE1) $(EXE2) $(DLL)

# Crear directorio bin si no existe
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compilar main-loader.exe
$(EXE1): $(SRC_EXE1) | $(BIN_DIR)
	@echo "Compilando y enlazando main-loader.c..."
	$(CC) $(CFLAGS) $(TARGET) $(SRC_EXE1) -o $(EXE1)

# Compilar main-loader-NOASLR.exe
$(EXE2): $(SRC_EXE2) | $(BIN_DIR)
	@echo "Compilando y enlazando main-loader-NOASLR.c..."
	$(CC) $(CFLAGS) $(TARGET) $(SRC_EXE2) -o $(EXE2)

# Compilar DLL
$(DLL): $(SRC_DLL) | $(BIN_DIR)
	@echo "Compilando DLL..."
	$(CC) $(CFLAGS) $(TARGET) -shared $(SRC_DLL) -o $(DLL)

run: $(EXE1)
	@echo "Ejecutando $(EXE1)..."
	$(RUN_CMD)

# Limpiar binarios
clean:
	@echo "Limpiando..."
	-rm -rf $(BIN_DIR)

.PHONY: all clean
