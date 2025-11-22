# =======================================
# LINUX
# =======================================
linux: bin/dllmock_messagebox.dll

bin/main-loader.exe: main-loader.c
	@echo "Compilando y enlazando main-loader.c..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s main-loader.c -o bin/main-loader.exe

bin/dllmock_messagebox.dll: dll/dllmock_messagebox.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dll/dllmock_messagebox.c -o bin/dllmock_messagebox.dll -shared

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin