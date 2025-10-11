all: dirs paso1

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

# ================
# BUILD
# ================
reflective_dll: dirs
	cl /nologo /W3 /MD /c dll\reflective.c /Fo:build\reflective.obj
	link /DLL /OUT:bin\reflective.dll build\reflective.obj

inject: dll
	cl /nologo /W3 /MD /I include /c c\main.c /Fo:build\main.obj
	link /OUT:bin\main.exe build\main.obj bin\reflective.lib

# ================
# TEST
# ================
paso1: mockdll victima
	cl /nologo /W3 /MD /c pasos\paso1.c /Fo:build\paso1.obj
	link /OUT:bin\paso1.exe build\paso1.obj

	.\bin\paso1.exe

paso2:
	cl /nologo /W3 /MD /I include /c pasos\paso1.c /Fo:build\paso1.c
	link /OUT:bin\paso1.exe build\paso1

paso3:
	cl /nologo /W3 /MD /I include /c pasos\paso1.c /Fo:build\paso1.c
	link /OUT:bin\paso1.exe build\paso1

mockdll: 
	cl /nologo /W3 /MD /Od /Zi /c pasos\utils\mockdll.c /Fo:build\mockdll.obj
	link /DLL /OUT:bin\mockdll.dll /DEBUG /PDB:bin\mockdll.pdb build\mockdll.obj


victima: 
	cl /nologo /W3 /MD /c pasos\utils\victima.c /Fo:build\victima.obj
	link /OUT:bin\victima.exe build\victima.obj


clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin