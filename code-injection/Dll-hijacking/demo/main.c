#include <stdio.h>
#include <windows.h>

typedef void (*hello_fn)();


int main(void) {
    printf("[+] Start \n");

    HMODULE module = LoadLibraryA("ws2_32.dll");
    printf("[+] Start 1 \n");

    getchar();

    hello_fn hello = (hello_fn)(module, "hello_from_dll");
    printf("[+] Start 2\n");
 
    hello();
    printf("[+] Start 3\n");

    FreeLibrary(module);

    printf("[+] End");
    return 0;
}
