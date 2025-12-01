# Shellcode x86 dev lab

## NASM

```
nasm -f bin .\reverse_shell\shell_x86.asm -o .\reverse_shell\shell_x86.bin
```
```
nasm -I . -f win32 runtime_linking.asm -o runtime_linking.obj
```

## Visual Studio 2022 Build tools

IMPORTANTE no funciona en powershell solo cmd

```
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars32"
```
```
cl /Zi /Fo"build\main.obj" /c main.c
```
```
link /OUT:"bin\main.exe" build\main.obj build\basics.obj /PDB:bin\main.pdb /DEBUG /ILK:build\main.ilk
```

## SCLAUNCHER

```
sclauncher.exe -f=".\main.bin" -pe -o="main.exe"
```

## NMAKE

> C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\Hostx86\x86\nmake.exe

```
namake
```




