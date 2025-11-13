TARGET   = bin/malicious.dll
SOURCE   = dll/malicious.c
DEF      = dll/proxy.def
CC       = x86_64-w64-mingw32-gcc
CFLAGS   = -Wall -s -O2 -shared
LDFLAGS  = -Wl,--def,$(DEF)

all: win

# =======================================
# WINDOWS
# =======================================
dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

clean_win:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin

win: dirs
	cl /LD /Fe:bin\real.dll dll\real.c /link /OUT:bin\real.dll

	cl /LD dll\malicious.c /link /DEF:dll\proxy.def /OUT:bin\malicious.dll

	cl main.c /Fe:bin\main.exe

hijack_win:
	move bin\real.dll bin\og_real.dll
	move bin\malicious.dll bin\real.dll


# =======================================
# LINUX
# =======================================
linux: bin/main.exe

bin/main.exe: main.c bin/real.dll bin/malicious.dll
	@echo "..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc main.c -o bin/main.exe -L./bin -lreal

bin/real.dll: dll/real.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared ./dll/real.c -o bin/real.dll -Wl,--out-implib,bin/real.lib

bin/malicious.dll: dll/malicious.c
	@echo "Compilando DLL..."
	@mkdir -p bin
# 	x86_64-w64-mingw32-dlltool -d dll/proxy.def -e dll/exports.o
# 	x86_64-w64-mingw32-gcc -shared -O2 dll/malicious.c dll/exports.o -o bin/malicious.dll
	@echo "Generando .def con dlltool..."
	x86_64-w64-mingw32-dlltool -z dll/proxy.def -D real.dll -o dll/exports.def
	@echo "Compilando DLL con exportaciones..."
	x86_64-w64-mingw32-gcc -Wall -O2 -shared dll/malicious.c -o bin/real.dll -Wl,--output-def,dll/exports.def,--out-implib,bin/libreal.a

hijack:
	mv bin/real.dll bin/og_real.dll
	mv bin/malicious.dll bin/real.dll


# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin