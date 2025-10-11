FILE_NAME = compilation_time
FILE_NAME_2 = run_time
DLL_NAME = my_dll
MYLOADER = myLoader

all: myLoader

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

myLoader: dirs dll
	cl /nologo /W3 /MD /I include /c $(MYLOADER).c /Fo:build\$(MYLOADER).obj
	link /OUT:bin\$(MYLOADER).exe build\$(MYLOADER).obj

	bin\$(MYLOADER).exe

dll: dirs
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