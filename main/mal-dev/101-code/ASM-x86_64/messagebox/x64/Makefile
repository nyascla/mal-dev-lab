ifeq ($(OS),Windows_NT)
    RM         = del /Q
    NULLDEV    = NUL
    TARGET     = -target x86_64-pc-windows-msvc
    RUN_CMD    = $(EXE)
else
    RM         = rm -rf
    NULLDEV    = /dev/null
    TARGET     = -target x86_64-w64-mingw32
    RUN_CMD    = wine $(EXE)
endif

build:
	@mkdir -p ./build
	nasm -f bin ./messagebox.asm -o ./build/messagebox.bin

bin:
	@mkdir -p bin


clean:
	@echo "Limpiando..."
	-$(RM) ./build 2>$(NULLDEV)

run: