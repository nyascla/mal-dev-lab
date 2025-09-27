#include <stdio.h>
#include <windows.h>

__declspec(dllimport) void hello_from_dll();


DWORD WINAPI threadFunc(LPVOID lpParam) {
    // code to run by the thread
    MessageBoxA(NULL, "Thread is running...", "WARNING", MB_ICONEXCLAMATION);
    return 0;
}


int main() {
    MessageBoxA(NULL, "__main__", "WARNING", MB_ICONEXCLAMATION);
    
    hello_from_dll();

    HANDLE hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, NULL);
    if (hThread == NULL) { return 1; }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    return 0;
}
