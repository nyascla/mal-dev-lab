
ifeq ($(OS),Windows_NT)
    CC = cl
else
    CC = x86_64-w64-mingw32-gcc
endif

# =======================================
# Windows
# =======================================
CC = cl
win:
	@echo "Compilando en Windows con $(CC)"

# =======================================
# LINUX
# =======================================
CC = x86_64-w64-mingw32-gcc
LDFLAGS = -luser32 
DLL_FLAGS = -shared $(LDFLAGS)

lin: aa

aa:
	@echo "Compilando en Linux con $(CC)"

main.exe: main.c lib.dll
	
	@echo "Enlazando el ejecutable final: main.exe"
	$(CC) main.c lib.dll -o main.exe $(LDFLAGS)

lib.dll: lib.c
	@echo "Compilando la biblioteca: lib"
	$(CC) lib.c -o lib.dll $(DLL_FLAGS)

clean:
	@echo "Limpiando archivos compilados..."
	rm -f main.exe lib.dll