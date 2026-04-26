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
DLL     = $(BIN_DIR)/dll.dll
DLL_LIB = $(BIN_DIR)/dll.lib

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -Wl,--out-implib=$(DLL_LIB)

# Fuentes
SRC_MAIN = main.c suma.c
SRC_DLL  = dll.c

all: $(DLL) $(EXE)

$(DLL): $(SRC_DLL)
	@echo "Compilando DLL para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) -shared -o $(DLL) $(SRC_DLL) $(LDFLAGS)

$(EXE): $(SRC_MAIN) $(DLL)
	@echo "Compilando main.exe para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_MAIN) $(DLL_LIB) -o $(EXE) 

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run
