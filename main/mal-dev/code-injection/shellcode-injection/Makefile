# =======================================
# Makefile Windows - MSVC
# =======================================
# Compilador
CC = cl

# Nombre del ejecutable
TARGET = local-loader.exe

# Fuentes
SRCS = local-loader.c

# Flags de compilación para DEBUG
CFLAGS = /Zi /Od /W4 /WX /EHsc
# /Zi   -> Genera información de depuración
# /Od   -> Desactiva optimizaciones
# /W4   -> Warning level 4 (máximo)
# /WX   -> Trata warnings como errores
# /EHsc -> Manejo de excepciones estándar C++

# Flags de linker para DEBUG
LDFLAGS = /DEBUG /INCREMENTAL
# /DEBUG       -> Genera .pdb con información de depuración
# /INCREMENTAL -> Linking incremental, útil en debug

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) /Fe:$(TARGET)

clean:
	del /f /q $(TARGET) *.obj *.pdb

# =======================================
# LINUX
# =======================================
linux: bin/local-loader.exe

bin/local-loader.exe: local-loader.c
	@echo "Compilando y enlazando main-loader.c..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s local-loader.c -o bin/loader-loader.exe

bin/dllmock_messagebox.dll: dll/dllmock_messagebox.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dll/dllmock_messagebox.c -o bin/dllmock_messagebox.dll -shared

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin