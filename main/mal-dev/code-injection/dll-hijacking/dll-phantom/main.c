#include <stdio.h>
#include <windows.h>

typedef void (*hello_fn)();


int main(void) {
    printf("[+] Start \n");

    // Como es una dll del sistema se carga primero la real que la maliciosa
    // C:\Windows\System32\ws2_32.dll
    HMODULE module = LoadLibraryA("ws2_32.dll");
    printf("[+] Module loaded at: %p\n", (void*)module);


    hello_fn hello = (hello_fn)(module, "hello_from_dll");
    printf("[+] Function address: %p\n", (void*)hello);
 
    hello();

    printf("[+] End");

    FreeLibrary(module);
    return 0;
}
