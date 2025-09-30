FILE_NAME = main

all: main

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

main: dirs
	cl /W3 /MDd /Zi /Od /c $(FILE_NAME).c /Fo:build\$(FILE_NAME).obj
	link /DEBUG /DYNAMICBASE /OUT:bin\$(FILE_NAME).exe build\$(FILE_NAME).obj

	dumpbin /headers main.exe | findstr "Dynamic base"

	bin\$(FILE_NAME).exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin


