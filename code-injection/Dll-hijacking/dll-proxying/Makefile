# =======================================
# LINUX (ok)
# =======================================
linux: bin/main.exe

bin/main.exe: main.c bin/real.dll bin/malicious.dll
	@echo "..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc main.c -o bin/main.exe -L./bin -lreal

bin/real.dll: dll-real.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared dll-real.c -o bin/real.dll -Wl,--out-implib,bin/real.lib

bin/malicious.dll: dll-malicious.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared -o bin/malicious.dll dll-malicious.c proxy.def -s

hijack:
	mv bin/real.dll bin/real-old.dll
	mv bin/malicious.dll bin/real.dll


clean:
	@echo "Limpiando..."
	@rm -rf bin