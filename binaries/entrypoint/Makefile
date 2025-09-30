CC      = cl
OBJS = build\main.obj build\exports.obj

	
all: dirs

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

build32: dirs
	cl c\simple.c /Zi /Od /MDd /Fe:bin\simple_x86.exe /Fo:build\simple_x86.obj

build64: dirs
	cl c\simple.c /Zi /Od /MDd /Fe:bin\simple_x64.exe /Fo:build\simple_x64.obj

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin