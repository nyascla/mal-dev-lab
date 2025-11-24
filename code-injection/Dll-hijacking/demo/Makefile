# =======================================
# WINDOWS (MSVC)
# =======================================

win: main.exe dll-evil.dll

main.exe: main.c
	@echo Compilando main.c...
	@if not exist bin mkdir bin
	cl /nologo /W3 /Zi /Od main.c /Fe:bin\main.exe

dll-evil.dll: dll-evil.c
	@echo Compilando DLL...
	@if not exist bin mkdir bin
	cl /nologo /W3 /Zi /Od /LD dll-evil.c /Fe:bin\dll-evil.dll /link user32.lib
	move /Y bin\dll-evil.dll bin\ws2_32.dll >nul

clean:
	@echo Limpiando...
	@if exist bin rmdir /S /Q bin

# =======================================
# LINUX
# =======================================

linux: bin/main.exe bin/dll-evil.dll

bin/main.exe: main.c
	@echo "Compilando y enlazando main-loader.c..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s main.c -o bin/main.exe

bin/dll-evil.dll: dll-evil.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dll-evil.c -o bin/dll-evil.dll -shared

	mv bin/dll-evil.dll bin/ws2_32.dll

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin