CC      = cl
OBJS = build\main.obj build\export.obj

	
all: dirs


dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

hello:
	cl hello.c

shell: objetos
	cl reverse_shell.c


clean:
