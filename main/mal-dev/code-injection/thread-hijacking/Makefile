ifeq ($(OS),Windows_NT)
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

# Salida
BIN_DIR 	= bin
ENTEROS_EXE 	= $(BIN_DIR)/enteros.exe
PUNTEROS_EXE    = $(BIN_DIR)/punteros.exe

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2

# Fuentes
SRC_ENTEROS = enteros.c
SRC_PUNTEROS = punteros.c

all: $(DLL) $(EXE)

enteros: $(SRC_MAIN) $(DLL)
	@echo "Compilando main.exe para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_ENTEROS) -o $(ENTEROS_EXE) 

punteros: $(SRC_MAIN) $(DLL)
	@echo "Compilando main.exe para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_PUNTEROS) -o $(PUNTEROS_EXE) 

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run
