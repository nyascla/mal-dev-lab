all: main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dll: dirs
	cl /nologo /W3 /MD /c dll\evil_dll.c /Fo:build\evil_dll.obj 
	link /DLL /OUT:bin\evil_dll.dll build\evil_dll.obj user32.lib

main: dll
	cl /nologo /W3 /MD /I include /c c\loader.c /Fo:build\loader.obj 
	link /OUT:bin\loader.exe build\loader.obj bin\evil_dll.lib user32.lib


clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin