CC = x86_64-w64-mingw32-gcc
# Flags linker
LDFLAGS = -luser32 
# Flags  para la DLL
DLL_FLAGS = -shared $(LDFLAGS)

all: main.exe

main.exe: main.c lib.dll
	@echo "Enlazando el ejecutable final: main.exe"
	$(CC) main.c lib.dll -o main.exe $(LDFLAGS)

lib.dll: lib.c
	@echo "Compilando la biblioteca: lib"
	$(CC) lib.c -o lib.dll $(DLL_FLAGS)

clean:
	@echo "Limpiando archivos compilados..."
	rm -f main.exe lib.dll