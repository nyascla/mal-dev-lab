#include <stdio.h>
#include <windows.h>

__declspec(dllimport) void hello_from_dll(void);

// Función del hilo
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    (void)lpParam; // Evita warning de variable no usada

    MessageBoxA(NULL, "Thread is running...", "INFO", MB_ICONEXCLAMATION);
    return 0;
}

int main(void) {
    MessageBoxA(NULL, "__main__", "INFO", MB_ICONEXCLAMATION);

    // Llamada a la función importada desde la DLL
    hello_from_dll();

    HANDLE threadHandle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);

    WaitForSingleObject(threadHandle, INFINITE);

    CloseHandle(threadHandle);

    MessageBoxA(NULL, "__exit__", "INFO", MB_ICONEXCLAMATION);
    return EXIT_SUCCESS;
}
