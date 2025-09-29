all: box patch

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

box: dirs
	nasm -f bin "asm/messagebox.asm" -o "build/messagebox.bin"
	sclauncher.exe -f="build/messagebox.bin" -pe -o="bin/messagebox.exe"

patch: dirs
	nasm -f bin "asm/messagebox_patch.asm" -o "build/messagebox_patch.bin"
	sclauncher.exe -f="build/messagebox_patch.bin" -pe -o="bin/messagebox_patch.exe"

clean:
	if exist build rmdir /s /q build
	if exist bin rmdir /s /q bin