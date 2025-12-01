CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -O2
SRC = test.c
OUT = test.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lws2_32

clean:
	rm -f $(OUT)

.PHONY: all clean
