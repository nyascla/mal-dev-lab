@echo off

del ".\main.exe" > nul 2>&1

if exist ".\main.exe" (
    echo [ERROR] El fichero esta abierto -_-
    exit /b 1
)

nasm -f bin .\main.asm -o .\main.bin

if %errorlevel% neq 0 (
    echo [ERROR] Fallo al ensamblar main.asm :\
    exit /b %errorlevel%
)

sclauncher.exe -f="main.bin" -pe -64 -o="main.exe" >nul 2>&1

echo [OK]
exit /b 0

