

all: linux

# =======================================
# WINDOWS
# =======================================
win:


# =======================================
# LINUX
# =======================================
linux:

bin/main.exe: main.c
	@echo "Compilando..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s main.c -o bin/main.exe

bin/original.dll: original.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s original.c -o bin/original.dll -shared

bin/malicius.dll: malicius.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s malicius.c -o bin/malicius.dll -shared -Wl,--out-implib,bin/libmalicius.a -Wl,--def, proxy.def

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin