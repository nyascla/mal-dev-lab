# Makefile que funciona idénticamente en Linux y Windows con Clang
ifeq ($(OS),Windows_NT)
    EXE     = hola.exe
    RM      = del /Q
    # En Windows usamos el target MSVC (usa UCRT + SDK de Windows, sin MinGW)
    TARGET  = -target x86_64-pc-windows-msvc
else
    EXE     = hola.exe
    RM      = rm -f
    # En Linux cross-compilamos a Windows con GNU (MinGW)
    TARGET  = -target x86_64-pc-windows-gnu
endif

CC      = clang
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -fuse-ld=lld

$(EXE): main.c
	$(CC) $(CFLAGS) $(TARGET) $(LDFLAGS) main.c -o $(EXE)

clean:
	-$(RM) $(EXE)

run: $(EXE)
	./$(EXE)

.PHONY: clean run