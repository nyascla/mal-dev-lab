# =======================================
# LINUX (ok)
# =======================================
linux: bin/main.exe

bin/main.exe: main.c
	@echo "..."
	@mkdir -p bin
	x86_64-w64-mingw32-gcc main.c -o bin/main.exe -lws2_32

clean:
	@echo "Limpiando..."
	@rm -rf bin