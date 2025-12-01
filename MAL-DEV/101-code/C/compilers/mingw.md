
# Mingw32

```bash
x86_64-w64-mingw32-gcc --version
```

## Template

```makefile
linux: bin/dll-staging-sliver.dll

bin/dll-staging-sliver.dll: dll-staging-sliver.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared -o dll-staging-sliver.dll dll-staging-sliver.c proxy.def -lws2_32 -s

test:
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared -o bin/dll-staging-sliver.dll dll-staging-sliver.c -lws2_32 -s
	x86_64-w64-mingw32-gcc -Wall -s main-test.c -o bin/main.exe

clean:
	@echo "Limpiando..."
	@rm -rf bin
```