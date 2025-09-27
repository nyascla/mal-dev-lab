call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars32"


cd "C:\Users\test\Desktop\mal-dev-lab\shelcodes\x86\runtime_linking"


nasm -I . -f win32 asm\runtime_linking.asm -o runtime_linking.obj


cl /Zi /Od /DEBUG main.c runtime_linking.obj


.\main.exe
