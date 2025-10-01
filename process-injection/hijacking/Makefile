FILE_NAME_2 = run_time
DLL_NAME = ws2_32

all: main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dll: dirs
	cl /nologo /W3 /MD /c dll\$(DLL_NAME).c /Fo:build\$(DLL_NAME).obj 
	link /DLL /OUT:bin\$(DLL_NAME).dll build\$(DLL_NAME).obj user32.lib


main: dll
	cl /nologo /W3 /MD /I include /c c\$(FILE_NAME_2).c /Fo:build\$(FILE_NAME_2).obj 
	link /OUT:bin\$(FILE_NAME_2).exe build\$(FILE_NAME_2).obj user32.lib

	bin\run_time.exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin