CC = cl /nologo /W3 /MD /c
BUILD = /Fo:build
BIN = 

all: main.exe

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

main.exe: main.c lib.dll
	$(CC) main.c /Fo:build\$(FILE_NAME).obj 
	link /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj bin\$(DLL_NAME).lib user32.lib


lib.dll:
	$(CC) dll.c /Fo:build\$(DLL_NAME).obj 
	link /DLL /OUT:bin\$(DLL_NAME).dll build\$(DLL_NAME).obj user32.lib




clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin