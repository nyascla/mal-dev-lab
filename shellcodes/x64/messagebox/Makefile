all: ccc

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

ccc: dirs
	cl /nologo /W3 /MD /I include /c c\messagebox.c /Fo:build\messagebox.obj 
	link /OUT:bin\messagebox.exe build\messagebox.obj user32.lib

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin