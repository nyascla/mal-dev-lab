NASM = "C:\Users\test\AppData\Local\bin\NASM\nasm.exe"
SC = "C:\Users\test\Desktop\win\sclauncher-main\sclauncher-main\sclauncher.exe"

# all: x86-shell
# =======================================
# runtime_linking
# =======================================

# =======================================
# reverse_shells
# =======================================
32_shell_path = reverse_shells\x86
32_shell_name = shell_x86
x86-shell: 
	!echo x86-shell...

	if not exist "$(32_shell_path)\build" mkdir "$(32_shell_path)\build"
    if not exist "$(32_shell_path)\bin" mkdir "$(32_shell_path)\bin"

	$(NASM) -f bin "$(32_shell_path)/$(32_shell_name).asm" -o "$(32_shell_path)/build/$(32_shell_name).bin"
	$(SC) -f="$(32_shell_path)/build/$(32_shell_name).bin" -pe -o="$(32_shell_path)/bin/$(32_shell_name).exe"


# =======================================
# messagebox
# =======================================
64_messagebox_path = messagebox\x64
64_messagebox_name = x64_messagebox
x64-messagebox:
	!echo x64-messagebox...

	if not exist "$(64_messagebox_path)\build" mkdir "$(64_messagebox_path)\build"
    if not exist "$(64_messagebox_path)\bin" mkdir "$(64_messagebox_path)\bin"

	$(NASM) -f bin "$(64_messagebox_path)/$(64_messagebox_name).asm" -o "$(64_messagebox_path)/build/$(64_messagebox_name).bin"
	$(SC) -f="$(64_messagebox_path)/build/$(64_messagebox_name).bin" -pe -64 -o="$(64_messagebox_path)/bin/$(64_messagebox_name).exe" >nul 2>&1

	"$(64_messagebox_path)\bin\$(64_messagebox_name).exe"

86_messagebox_path = messagebox\x86
86_messagebox_name = messagebox
x86-messagebox:
	!echo x86-messagebox...

	if not exist "$(86_messagebox_path)\build" mkdir "$(86_messagebox_path)\build"
    if not exist "$(86_messagebox_path)\bin" mkdir "$(86_messagebox_path)\bin"

	$(NASM) -f bin "$(86_messagebox_path)/$(86_messagebox_name).asm" -o "$(86_messagebox_path)/build/$(86_messagebox_name).bin"
	$(SC) -f="$(86_messagebox_path)/build/$(86_messagebox_name).bin" -pe -o="$(86_messagebox_path)/bin/$(86_messagebox_name).exe" >nul 2>&1

	"$(86_messagebox_path)\bin\$(86_messagebox_name).exe"