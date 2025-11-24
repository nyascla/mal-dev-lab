# =======================================
# LINUX
# =======================================
linux: bin/dllmock_messagebox.dll bin/dllmock_printf.dll


bin/dllmock_printf.dll: dllmock_printf.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dllmock_printf.c -o bin/dllmock_printf.dll -shared

bin/dllmock_messagebox.dll: dllmock_messagebox.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dllmock_messagebox.c -o bin/dllmock_messagebox.dll -shared

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin