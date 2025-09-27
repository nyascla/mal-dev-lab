CC      = cl

	
all: run

nasm:
	nasm -f win32 asm\basics.asm -o build\basics.obj

cl: nasm
	$(CC) /Zi /Fo"build\main.obj" /c main.c
	link /OUT:"bin\main.exe" build\main.obj build\basics.obj /PDB:bin\main.pdb /DEBUG /ILK:build\main.ilk

run: cl
	bin\main.exe

clean:
	if exist vc140.pdb del vc140.pdb

	if exist bin\main.exe del bin\main.exe
	if exist bin\main.pdb del bin\main.pdb

	if exist build\basics.obj del build\basics.obj
	if exist build\main.obj del build\main.obj
	if exist build\main.ilk del build\main.ilk




