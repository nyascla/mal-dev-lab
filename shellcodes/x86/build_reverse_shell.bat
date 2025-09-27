@echo off

del ".\reverse_shell.exe" > nul 2>&1

if exist ".\reverse_shell.exe" (
    echo [ERROR] El fichero esta abierto -_-
    exit /b 1
)

nasm -f bin .\reverse_shell\shell_x86.asm -o .\reverse_shell\shell_x86.bin

if %errorlevel% neq 0 (
    echo [ERROR] Fallo al ensamblar main.asm :\
    exit /b %errorlevel%
)

sclauncher.exe -f=".\reverse_shell\shell_x86.bin" -pe -o="reverse_shell.exe"

echo [OK]
exit /b 0

