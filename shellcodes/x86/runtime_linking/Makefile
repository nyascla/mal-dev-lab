CC      = cl
OBJS = build\main.obj build\exports.obj

	
all: tests


dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

proc:
	nasm -f bin "asm/get_proc_address.asm" -o "build/get_proc_address.bin"
	sclauncher.exe -f="build/get_proc_address.bin" -pe -o="bin/get_proc_address.exe"

tests: objetos
	!echo Compilando...

	nasm -f win32 "asm/exports.asm" -o "build/exports.obj"


	cl /Zi /Fo"build\main.obj" /c test\main.c
	link /OUT:"bin\main.exe" $(OBJS) /PDB:bin\main.pdb /DEBUG /ILK:build\main.ilk

	bin\main.exe


clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin