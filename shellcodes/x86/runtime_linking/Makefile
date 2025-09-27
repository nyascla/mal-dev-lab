CC      = cl
OBJS = build\main.obj build\export.obj

	
all: dirs


dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

proc:
	nasm -f bin "asm/get_proc_address.asm" -o "build/get_proc_address.bin"
	sclauncher.exe -f="build/get_proc_address.bin" -pe -o="bin/get_proc_address.exe"

objetos:
	nasm -f win32 "asm/export.asm" -o "build/export.obj"

tests: objetos
	cl /Zi /Fo"build\main.obj" /c main.c
	link /OUT:"bin\main.exe" $(OBJS) /PDB:bin\main.pdb /DEBUG /ILK:build\main.ilk
	bin\main.exe


clean:
	if exist vc140.pdb del vc140.pdb
	if exist bin\main.exe del bin\main.exe
	if exist bin\main.pdb del bin\main.pdb
	if exist build\runtime_linking.obj del build\runtime_linking.obj
	if exist build\main.obj del build\main.obj
	if exist build\main.ilk del build\main.ilk