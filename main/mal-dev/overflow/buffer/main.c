#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT     "9000"
#define BUFSIZE  512

void handle_client(SOCKET client) {
    char buffer[BUFSIZE];
    int bytesRecv;

    bytesRecv = recv(client, buffer, BUFSIZE - 1, 0);

    if (bytesRecv == SOCKET_ERROR) {
        printf("[-] Error en recv(): %d\n", WSAGetLastError());
        return;
    }

    buffer[bytesRecv] = '\0';

    // ✅ Quitamos el \n o \r\n que manda netcat/telnet
    buffer[strcspn(buffer, "\r\n")] = '\0';

    printf("[+] Recibido (%d bytes): %s\n", bytesRecv, buffer);

    // ✅ Comprobamos si el cliente quiere salir
    if (strcmp(buffer, "exit") == 0) {
        printf("[+] Cliente envió 'exit', cerrando conexión.\n");
        send(client, "Hasta luego!\n", 13, 0);
        return;  // salimos de handle_client → el bucle cierra el socket
    }

    char respuesta[BUFSIZE];
    snprintf(respuesta, sizeof(respuesta), "Hola! Recibí: %s\n", buffer);
    send(client, respuesta, (int)strlen(respuesta), 0);
}

int main(void) {
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, hints;

    // 1. Inicializar Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("[-] WSAStartup falló\n");
        return 1;
    }

    // 2. Configurar hints para getaddrinfo
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;  // bind a todas las interfaces

    // 3. Resolver dirección local
    if (getaddrinfo(NULL, PORT, &hints, &result) != 0) {
        printf("[-] getaddrinfo falló\n");
        WSACleanup();
        return 1;
    }

    // 4. Crear socket
    ListenSocket = socket(result->ai_family,
                          result->ai_socktype,
                          result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("[-] socket() falló: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // 5. Bind
    if (bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("[-] bind() falló: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    // 6. Listen
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("[-] listen() falló: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    printf("[+] Escuchando en puerto %s...\n", PORT);

    while (1) {  // ← bucle infinito, acepta conexiones para siempre
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("[-] accept() falló: %d\n", WSAGetLastError());
            break;  // salimos del bucle si hay error grave
        }
        printf("[+] Cliente conectado.\n");

        handle_client(ClientSocket);  // maneja la conexión

        closesocket(ClientSocket);    // cierra ESTE cliente
        printf("[+] Cliente desconectado, esperando otro...\n");
        // vuelve al while → espera la siguiente conexión
    }

    // 8. Manejar cliente de forma segura
    handle_client(ClientSocket);

    // 9. Cerrar todo limpiamente
    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();
    printf("[+] Servidor cerrado.\n");
    return 0;
}