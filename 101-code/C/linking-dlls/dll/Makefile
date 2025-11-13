DLL_NAME = dllmock

all: bin/dllmock.dll

# =======================================
# WINDOWS
# =======================================
dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dll: dirs
	cl /nologo /W3 /MD /c dll\$(DLL_NAME).c /Fo:build\$(DLL_NAME).obj 
	link /DLL /OUT:bin\$(DLL_NAME).dll build\$(DLL_NAME).obj user32.lib

clean_win:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin

# =======================================
# LINUX
# =======================================

bin/dllmock.dll: dllmock.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared dllmock.c -o bin/dllmock.dll -Wl,--out-implib,bin/dllmock.lib

clean:
	@echo "Limpiando..."
	@rm -rf bin build