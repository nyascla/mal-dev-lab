all: main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dll: dirs
	cl /nologo /W3 /MD /c dll\reflective.c /Fo:build\reflective.obj
	link /DLL /OUT:bin\reflective.dll build\reflective.obj

main: dll
	cl /nologo /W3 /MD /I include /c c\main.c /Fo:build\main.obj
	link /OUT:bin\main.exe build\main.obj bin\reflective.lib


clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin