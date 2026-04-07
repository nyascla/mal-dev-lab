BASE_NAME = simple_x86
CFG_NAME = simple_x86_cfg


all: build32 cfg

dirs:
	if not exist build mkdir build
	if not exist bin_v2 mkdir bin_v2
	if not exist bin mkdir bin

build32: dirs
	cl simple.c /Zi /Od /MDd /Fe:bin\$(BASE_NAME).exe /Fo:build\$(BASE_NAME).obj

cfg: dirs
	cl simple.c /Zi /Od /MDd /guard:cf /GS /Fe:bin\$(CFG_NAME).exe /Fo:build\$(CFG_NAME).obj


clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin
	if exist bin_v2 rmdir /s /q bin_v2

	