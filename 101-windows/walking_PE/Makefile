FILE_NAME = peSections
DLL = dll_simple
TEST = test
MAIN = main

all: dirs main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dlls:
	cl /W3 /MD /c dll\$(DLL).c /Fo:build\$(DLL).obj
	link /DLL /OUT:bin\$(DLL).dll build\$(DLL).obj

test_dll: dlls
	cl /nologo /W3 /MD /I include /c dll\$(TEST).c /Fo:build\$(TEST).obj
	link /DEBUG /OUT:bin\$(TEST).exe build\$(TEST).obj bin\$(DLL).lib

	bin\$(TEST).exe

peSections: dlls
	cl /nologo /W3 /MD /I include /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
	link /DEBUG /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj

	bin\$(FILE_NAME).exe

main:
	cl /nologo /W3 /MD /I include /c $(MAIN).c /Fo:build\$(MAIN).obj
	link /DEBUG /OUT:bin\$(MAIN).exe build\$(MAIN).obj

	bin\$(MAIN).exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin

# =======================================
# LINUX
# =======================================
linux: bin/main.exe

bin/main.exe: main.c bin/dllmock.dll
	@echo "Compilando y enlazando main.c..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s main.c -o bin/main.exe

bin/dllmock.dll: dllmock.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dllmock.c -o bin/dllmock.dll -shared

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf bin