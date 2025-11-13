
all: bin/main.exe

# =======================================
# WINDOWS
# =======================================

# =======================================
# LINUX
# =======================================

# NOTA: mingw32 ignora pragma ya que es sintaxis específica de MSVC (Microsoft Visual C++).
bin/main.exe: main.c
	@echo "..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc main.c -o bin/main.exe -L../dll/bin -ldllmock

	cp ../dll/bin/dllmock.dll ./bin/dllmock.dll

clean:
	@echo "Limpiando..."
	@rm -rf bin build