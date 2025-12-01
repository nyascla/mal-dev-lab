# =======================================
# Configuración multiplataforma
# =======================================

ifeq ($(OS),Windows_NT)
    BIN_DIR    = bin
    EXE        = main.exe
    DLL        = dll-staging-sliver.dll
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    BIN_DIR    = bin
    EXE        = $(BIN_DIR)/main.exe
    DLL        = $(BIN_DIR)/dll-staging-sliver.dll
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -fuse-ld=lld

# Fuentes
SRC_DLL = src/dll-sliver-stage2.c
SRC_EXE = src/main.c
PROXY = def-file/proxy.def


# =======================================
# Targets
# =======================================

all: $(DLL)

# Compilación DLL
$(DLL): $(SRC_DLL)
	@echo "Compilando DLL..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) -shared -o $(DLL) $(SRC_DLL) -Wl,def-file/proxy.def -lws2_32 $(LDFLAGS) -s
# Compilación test
test: $(SRC_DLL) $(SRC_EXE)
	@echo "Compilando test..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_EXE) -o $(EXE) $(LDFLAGS) -s

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all test clean run
