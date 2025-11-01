FILE_NAME = main

all:

# =======================================
# LINUX
# =======================================
linux: bin/main.exe

bin/main.exe: main.c
	@echo "Compilando y enlazando main.c..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s main.c -o bin/main.exe

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin