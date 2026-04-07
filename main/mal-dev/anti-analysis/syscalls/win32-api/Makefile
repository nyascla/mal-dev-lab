# =======================================
# Configuración multiplataforma
# =======================================

ifeq ($(OS),Windows_NT)
    BIN_DIR    = bin
    EXE        = main.exe
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    BIN_DIR    = bin
    EXE        = $(BIN_DIR)/main.exe
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2

# Fuentes
SRC_MAIN = loader.c

# =======================================
# Targets
# =======================================

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
