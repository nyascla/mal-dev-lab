ifeq ($(OS),Windows_NT)
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target i686-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

# Salida
BIN_DIR = bin
OBJ_DIR = obj
EXE     = bin/main.exe
OBJ     = obj/funcion.o

# Fuentes
SRC_MAIN = main.c $(OBJ)
SRC_F = f.asm


# Compilador y flags
CC      = clang
CFLAGS  = -m32

all: $(EXE)

$(EXE): 
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@echo ""

	nasm -f elf32 f.asm -o $(OBJ)
	$(CC) $(CFLAGS) $(SRC_MAIN) -o $(EXE) 

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)
	-$(RM) $(OBJ_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run
