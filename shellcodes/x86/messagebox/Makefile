all: shell

dirs:
	if not exist build mkdir build
	if not exist bin mkdir bin

shell: dirs
	nasm -f bin "asm/messagebox.asm" -o "build/messagebox.bin"
	sclauncher.exe -f="build/messagebox.bin" -pe -o="bin/messagebox.exe"

clean:
