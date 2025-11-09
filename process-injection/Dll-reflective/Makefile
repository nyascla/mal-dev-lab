INJECT = injector
DLL = dllReflective
TEST = test

all: dirs paso1

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

# ================
# test injector
mockdll: 
	cl /nologo /W3 /MD /Od /Zi /c utils\mockdll.c /Fo:build\mockdll.obj
	link /DLL /OUT:bin\mockdll.dll /DEBUG /PDB:bin\mockdll.pdb build\mockdll.obj

victima: 
	cl /nologo /W3 /MD /c utils\victima.c /Fo:build\victima.obj
	link /OUT:bin\victima.exe build\victima.obj

injector: dirs mockdll victima
	cl /nologo /W3 /MD /c $(INJECT).c /Fo:build\$(INJECT).obj
	link /OUT:bin\$(INJECT).exe build\$(INJECT).obj

	.\bin\$(INJECT).exe

# ================
# test dllReflevtive
dllReflevtive:
	cl /nologo /W3 /MD /Od /Zi /c $(DLL).c /Fo:build\$(DLL).obj 
	link /DLL /OUT:bin\$(DLL).dll /DEBUG /PDB:bin\$(DLL).pdb build\$(DLL).obj

test: dirs dllReflevtive
	cl /nologo /W3 /MD /Od /Zi /c utils\$(TEST).c /Fo:build\$(TEST).obj
	link /OUT:bin\$(TEST).exe /DEBUG /PDB:bin\$(TEST).pdb build\$(TEST).obj bin\$(DLL).lib
 
	.\bin\$(TEST).exe

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin