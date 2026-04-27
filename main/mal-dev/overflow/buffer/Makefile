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

BIN_DIR = bin
EXE     = $(BIN_DIR)/main.exe
CC      = clang

# ⚠️  FLAGS VULNERABLES — eliminamos TODAS las protecciones:
#   -O0                  → sin optimización (stack más predecible)
#   -fno-stack-protector → desactiva stack canary (cookie de protección)
#   -z execstack         → stack ejecutable (permite ejecutar shellcode)
#   -D_FORTIFY_SOURCE=0  → desactiva chequeos de funciones peligrosas
#   -mno-sse2            → evita que el compilador use registros XMM
#                          que alinean el stack de forma impredecible
CFLAGS  = -O0 \
           -fno-stack-protector \
           -z execstack \
           -D_FORTIFY_SOURCE=0 \
           -mno-sse2 \
           -Wno-deprecated-declarations

LDFLAGS = -lws2_32

SRC_MAIN = main.c

all: $(EXE)

$(EXE): $(SRC_MAIN)
	@echo "Compilando main.exe VULNERABLE para Windows..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) $(SRC_MAIN) $(LDFLAGS) -o $(EXE)

clean:
	@echo "Limpiando..."
	-$(RM) $(BIN_DIR) 2>$(NULLDEV)

run: $(EXE)
	@echo "Ejecutando $(EXE)..."
	$(RUN_CMD)

.PHONY: all clean run