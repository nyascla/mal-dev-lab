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
BIN_DIR = bin
EXE     = $(BIN_DIR)/main.exe

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2

# Fuentes
SRC_MAIN = main.c

all: $(EXE)

$(EXE): $(SRC_MAIN) $(DLL)
	@echo "Compilando main.exe para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_MAIN) -o $(EXE) 

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run