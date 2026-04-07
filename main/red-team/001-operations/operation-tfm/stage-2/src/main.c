#include <windows.h>
#include <stdio.h>            

int main(){
    printf("[+] Run Test \n");

    LoadLibraryA("dll-staging-sliver.dll");

    getchar();

    return 1;
}