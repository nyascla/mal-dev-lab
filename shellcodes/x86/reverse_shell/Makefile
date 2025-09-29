all: shell

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

shell: dirs
	nasm -f bin "asm/shell_x86.asm" -o "build/shell_x86.bin"
	sclauncher.exe -f="build/shell_x86.bin" -pe -o="bin/shell_x86.exe"

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin