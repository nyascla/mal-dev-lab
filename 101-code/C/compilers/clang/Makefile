# =========================================
# Makefile multiplataforma: Linux y Windows
# =========================================

# Detectar SO
ifeq ($(OS),Windows_NT)
    EXE        = hola.exe
    RM         = del /Q
    NULLDEV    = NUL
    # Target: MSVC ABI nativo o Windows con Clang
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    EXE        = hola.exe
    RM         = rm -f
    NULLDEV    = /dev/null
    # Cross-compilación Windows desde Linux
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -fuse-ld=lld

# Fuentes y objetos
SRC     = main.c
OBJ     = $(SRC:.c=.o)

# =========================================
# Reglas principales
# =========================================

all: $(EXE)

# Compilación y linking en una sola línea
$(EXE): $(SRC)
	@echo "Compilando $(EXE) para $(OS)..."
	$(CC) $(CFLAGS) $(TARGET) $(SRC) -o $(EXE) $(LDFLAGS)

clean:
	@echo "Limpiando archivos compilados..."
	-$(RM) $(EXE) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run
