# =======================================
# LINUX (con Clang + LLD)
# =======================================

CC       = clang
TARGET   = -target x86_64-w64-mingw32
CFLAGS   = -Wall -Wextra -O2
LDFLAGS  = -fuse-ld=lld

BIN_DIR  = bin

# ---------------------------------------
# REGRA PRINCIPAL
# ---------------------------------------
linux: $(BIN_DIR)/main.exe

# ---------------------------------------
# MAIN
# ---------------------------------------
$(BIN_DIR)/main.exe: main.c $(BIN_DIR)/real.dll $(BIN_DIR)/malicious.dll
	@echo "Compilando main.exe..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) main.c -o $(BIN_DIR)/main.exe \
	    -L./$(BIN_DIR) -lreal $(LDFLAGS)

# ---------------------------------------
# DLL REAL
# ---------------------------------------
$(BIN_DIR)/real.dll: dll-real.c
	@echo "Compilando real.dll..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) -shared dll-real.c -o $(BIN_DIR)/real.dll \
	    -Wl,--out-implib,$(BIN_DIR)/real.lib $(LDFLAGS)

# ---------------------------------------
# DLL MALICIOSA (PROXY)
# ---------------------------------------
$(BIN_DIR)/malicious.dll: dll-malicious.c proxy.def
	@echo "Compilando malicious.dll..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TARGET) -shared dll-malicious.c -o $(BIN_DIR)/malicious.dll \
	    -Wl,proxy.def -s $(LDFLAGS)

# ---------------------------------------
# HIJACK (reemplazar DLL real por maliciosa)
# ---------------------------------------
hijack:
	mv $(BIN_DIR)/real.dll $(BIN_DIR)/real-old.dll
	mv $(BIN_DIR)/malicious.dll $(BIN_DIR)/real.dll

# ---------------------------------------
# CLEAN
# ---------------------------------------
clean:
	@echo "Limpiando..."
	@rm -rf $(BIN_DIR)

.PHONY: linux hijack clean
