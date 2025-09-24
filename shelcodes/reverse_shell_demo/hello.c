#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>

#define ATTACKER_IP "127.0.0.1"
#define ATTACKER_PORT 5000

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error inicializando Winsock\n");
        return 1;
    }

    // Create socket
    SOCKET sock;
    sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error creando socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Connect     
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ATTACKER_IP);
    server.sin_port = htons(ATTACKER_PORT);
    if (WSAConnect(sock, (SOCKADDR*)&server, sizeof(server), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
        printf("Error conectando: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Enviar mensaje
    const char *msg = "Hello from client\n";
    int to_send = (int)strlen(msg);
    int sent = send(sock, msg, to_send, 0);
    
    if (sent == SOCKET_ERROR) {
        printf("Error en send: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Enviados %d bytes\n", sent);

    // Recibir respuesta
    char buf[1024];
    int recvd = recv(sock, buf, sizeof(buf) - 1, 0);
    if (recvd == SOCKET_ERROR) {
        printf("Error en recv: %d\n", WSAGetLastError());
    } else if (recvd == 0) {
        printf("Conexión cerrada por el servidor\n");
    } else {
        buf[recvd] = '\0';
        printf("Respuesta del servidor: %s\n", buf);
    }

    // Cierre
    shutdown(sock, SD_SEND); /* indica que ya no envías más datos */
    closesocket(sock);
    WSACleanup();
    return 0;
}