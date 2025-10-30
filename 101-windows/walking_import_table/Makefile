FILE_NAME = main

all: main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

main: dirs
	cl /nologo /W3 /MD /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
	link /DEBUG /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj

	bin\$(FILE_NAME).exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin