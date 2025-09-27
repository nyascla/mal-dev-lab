del ".\test.exe" > nul 2>&1

if exist ".\test.exe" (
    echo [ERROR] El fichero esta abierto -_-
    exit /b 1
)

call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars32"


cd "C:\Users\test\Desktop\mal-dev-lab\shelcodes\x86\runtime_linking"


nasm -I . -f win32 runtime_linking.asm -o runtime_linking.obj


cl /Zi /Od /DEBUG test.c runtime_linking.obj


.\test.exe
