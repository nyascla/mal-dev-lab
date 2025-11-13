#include <stdio.h>


__declspec(dllimport) void FuncA();
__declspec(dllimport) void FuncB();
__declspec(dllimport) void FuncC();

// solo para MSVC
#pragma comment(lib, ".bin/real.lib")

int main() {
    printf("[MAIN] Hello from main!\n");
    
    FuncA();
    FuncB();
    FuncC();

    printf("[MAIN] Goodbye from main!\n");
    return 0;
}