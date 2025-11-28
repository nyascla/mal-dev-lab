# Makefile que funciona 100% igual en Linux y Windows (con Clang instalado)

# Detecta automáticamente si estamos en Windows o Linux
ifeq ($(OS),Windows_NT)
    # En Windows nativo (o WSL con clang de Chocolatey)
    EXE    = hola.exe
    RM     = del /Q
else
    # En Linux (o WSL)
    EXE    = hola.exe
    RM     = rm -f
endif

# Compilador y flags
CC      = clang
CFLAGS  = -Wall -Wextra -O2
# Forzamos siempre target Windows para que genere .exe válido
TARGET  = -target x86_64-pc-windows-gnu
LDFLAGS = -fuse-ld=lld          # linker rápido (opcional pero recomendado)

# Regla principal
$(EXE): main.c
	$(CC) $(CFLAGS) $(TARGET) $(LDFLAGS) main.c -o $(EXE)

# Limpiar
clean:
	$(RM) $(EXE)

# Compilar y ejecutar (solo funciona en Windows o WSL)
run: $(EXE)
	./$(EXE)

.PHONY: clean run