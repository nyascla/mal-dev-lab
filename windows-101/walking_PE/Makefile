FILE_NAME = peSections
DLL = dll_simple
TEST = test

all: dirs main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

dlls:
	cl /W3 /MD /c dll\$(DLL).c /Fo:build\$(DLL).obj
	link /DLL /OUT:bin\$(DLL).dll build\$(DLL).obj

test: dlls
	cl /nologo /W3 /MD /I include /c dll\$(TEST).c /Fo:build\$(TEST).obj
	link /DEBUG /OUT:bin\$(TEST).exe build\$(TEST).obj bin\$(DLL).lib

	bin\$(TEST).exe

main: dlls
	cl /nologo /W3 /MD /I include /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
	link /DEBUG /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj

	bin\$(FILE_NAME).exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin