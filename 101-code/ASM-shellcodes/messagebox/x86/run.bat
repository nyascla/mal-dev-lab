@echo off
setlocal

:: Nombre del programa (sin extensión)
set "PROGRAM_NAME=messagebox"

:: Rutas de los ejecutables
set "NASM_EXECUTABLE=C:\Users\test\AppData\Local\bin\NASM\nasm.exe"
set "SCLAUNCHER_EXECUTABLE=C:\Users\test\Desktop\win\sclauncher-main\sclauncher-main\sclauncher.exe"

:: Elimina el exe si existe
del ".\bin\%PROGRAM_NAME%.exe" > nul 2>&1

if exist ".\bin\%PROGRAM_NAME%.exe" (
    echo [ERROR] El fichero esta abierto -_-
    exit /b 1
)

:: Ensamblar
"%NASM_EXECUTABLE%" -f bin ".\%PROGRAM_NAME%.asm" -o ".\build\%PROGRAM_NAME%.bin"

if %errorlevel% neq 0 (
    echo [ERROR] Fallo al ensamblar %PROGRAM_NAME%.asm
    exit /b %errorlevel%
)

:: Ejecutar sclauncher
"%SCLAUNCHER_EXECUTABLE%" -f="build/%PROGRAM_NAME%.bin" -pe -o="bin/%PROGRAM_NAME%.exe" > nul 2>&1

if %errorlevel% neq 0 (
    echo [ERROR] Fallo al crear el ejecutable %PROGRAM_NAME%.exe
    exit /b %errorlevel%
)

echo [OK]

exit /b 0
