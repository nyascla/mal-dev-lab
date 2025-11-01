FILE_NAME = compilation_time
FILE_NAME_2 = run_time
DLL_NAME = my_dll
MYLOADER = myLoader

all: linux


# =======================================
# WINDOWS
# =======================================
win:

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

myLoader-win: dirs dll
	cl /nologo /W3 /MD /I include /c $(MYLOADER).c /Fo:build\$(MYLOADER).obj
	link /OUT:bin\$(MYLOADER).exe build\$(MYLOADER).obj

	bin\$(MYLOADER).exe

dll:
	cl /nologo /W3 /MD /c dll\$(DLL_NAME).c /Fo:build\$(DLL_NAME).obj 
	link /DLL /OUT:bin\$(DLL_NAME).dll build\$(DLL_NAME).obj user32.lib

compilation: dll
	cl /nologo /W3 /MD /I include /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj 
	link /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj bin\$(DLL_NAME).lib user32.lib

run: dll
	cl /nologo /W3 /MD /I include /c $(FILE_NAME_2).c /Fo:build\$(FILE_NAME_2).obj 
	link /OUT:bin\$(FILE_NAME_2).exe build\$(FILE_NAME_2).obj user32.lib

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin

# =======================================
# LINUX
# =======================================
linux: bin/main.exe

# Depende de los dos archivos .o y de la .dll
bin/main.exe: build/main.o build/headers.o bin/dllmock.dll
	@echo "Enlazando ejecutable..."
	x86_64-w64-mingw32-gcc -s build/main.o build/headers.o bin/dllmock.dll -o bin/main.exe

# Regla para compilar main.o
build/main.o: main.c
	@echo "Compilando main.c..."
	@mkdir -p build
	x86_64-w64-mingw32-gcc -Wall -c main.c -o build/main.o

# Regla para compilar headers.o
build/headers.o: headers.c
	@echo "Compilando headers.c..."
	@mkdir -p build
	x86_64-w64-mingw32-gcc -Wall -c headers.c -o build/headers.o

# Regla para compilar la DLL
bin/dllmock.dll: dll/dllmock.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -Wall -s dll/dllmock.c -o bin/dllmock.dll -shared

# Regla para limpiar los directorios
clean:
	@echo "Limpiando..."
	@rm -rf bin build