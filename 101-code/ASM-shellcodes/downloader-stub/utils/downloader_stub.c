#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet.lib")

int main() {
    HINTERNET hSession, hConnect;
    FILE* pFile;
    char buffer[1024];
    DWORD bytesRead;

    // 1. Iniciar sesión y abrir URL
    hSession = InternetOpenA("MiApp", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
    hConnect = InternetOpenUrlA(hSession, "https://curl.se/ca/cacert.pem", 0, 0, INTERNET_FLAG_RELOAD, 0);

    // 2. Abrir archivo local
    pFile = fopen("fichero_descargado.pem", "wb");

    // 3. Bucle de descarga/escritura (lee de internet, escribe en disco)
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        fwrite(buffer, 1, bytesRead, pFile);
    }

    // 4. Limpieza
    fclose(pFile);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);

    printf("Descarga finalizada.\n");
    return 0;
}