# --- Variables de Compilación ---

# Define el compilador que vamos a usar
CC = x86_64-w64-mingw32-gcc

# Banderas comunes del enlazador (Linker)
LDFLAGS = -luser32

# Banderas específicas para la DLL (añade -shared)
DLL_FLAGS = -shared $(LDFLAGS)

# --- Objetivos (Targets) ---

# El objetivo por defecto (lo que se ejecuta si solo escribes 'make')
# Le decimos que 'all' depende de 'main.exe'
all: main.exe

# Regla para construir el ejecutable (main.exe)
# Depende de su código (main.c) y de la DLL (milib.dll)
main.exe: main.c milib.dll
	@echo "Enlazando el ejecutable final: main.exe"
	$(CC) main.c milib.dll -o main.exe $(LDFLAGS)

# Regla para construir la biblioteca (milib.dll)
# Depende solo de su código (milib.dll.c)
milib.dll: milib.dll.c
	@echo "Compilando la biblioteca: milib.dll"
	$(CC) milib.dll.c -o milib.dll $(DLL_FLAGS)

# Regla para limpiar los archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	rm -f main.exe milib.dll