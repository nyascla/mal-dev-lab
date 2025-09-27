#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>


#pragma comment(lib, "ws2_32.lib")


void main() {
    printf("=== SIZEOF ===\n");
    printf("WSADATA: 0x%X\n", sizeof(WSADATA));
    printf("SOCKET: 0x%X\n", sizeof(SOCKET));
    printf("sockaddr_in: 0x%X\n", sizeof(struct sockaddr_in));
    printf("STARTUPINFO: 0x%X\n", sizeof(STARTUPINFO));
    printf("PROCESS_INFORMATION: 0x%X\n", sizeof(PROCESS_INFORMATION));

    printf("\n");
    printf("=== OFFSETOF ===\n");
    printf("PROCESS_INFORMATION: 0x%X\n", (unsigned)offsetof(PROCESS_INFORMATION, hProcess));
}


