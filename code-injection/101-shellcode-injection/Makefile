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