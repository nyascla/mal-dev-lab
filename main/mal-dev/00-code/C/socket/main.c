#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// Directiva útil si se compila en Windows nativo (MSVC o Clang-CL), 
// aunque en el entorno cruzado (MinGW) lo enlazaremos en el Makefile.
#pragma comment(lib, "Ws2_32.lib")

int main(void) {
    WSADATA wsaData;
    int iResult;

    // 1. Inicializar Winsock (solicitamos la versión 2.2)
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("[-] WSAStartup ha fallado con el error: %d\n", iResult);
        return 1;
    }
    printf("[+] Winsock inicializado correctamente.\n");

    // 2. Crear un SOCKET (AF_INET = IPv4, SOCK_STREAM = TCP)
    SOCKET ConnectSocket = INVALID_SOCKET;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (ConnectSocket == INVALID_SOCKET) {
        printf("[-] Error en socket(): %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("[+] Socket creado correctamente.\n");

    // [Aquí iría la lógica de red (bind, connect, listen, accept, send, recv)]

    // 3. Cerrar el socket limpiamente
    iResult = closesocket(ConnectSocket);
    if (iResult == SOCKET_ERROR) {
        printf("[-] closesocket ha fallado con el error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("[+] Socket cerrado correctamente.\n");

    // 4. Limpiar los recursos usados por Winsock
    WSACleanup();
    printf("[+] Limpieza de Winsock completada.\n");

    return 0;
}
