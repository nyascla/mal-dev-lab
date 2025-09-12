@echo off

del ".\messagebox.exe" > nul 2>&1

if exist ".\messagebox.exe" (
    echo [ERROR] El fichero esta abierto -_-
    exit /b 1
)

nasm -f bin .\messagebox\messagebox.asm -o .\messagebox\messagebox.bin

if %errorlevel% neq 0 (
    echo [ERROR] Fallo al ensamblar main.asm :\
    exit /b %errorlevel%
)

sclauncher.exe -f=".\messagebox\messagebox.bin" -pe -o="messagebox.exe"

echo [OK]
exit /b 0

