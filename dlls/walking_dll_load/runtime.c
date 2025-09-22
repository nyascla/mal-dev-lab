#include <stdio.h>
#include <windows.h>

typedef void (*hello_fn)();


DWORD WINAPI threadFunc(LPVOID lpParam) {
    // code to run by the thread
    MessageBoxA(NULL, "Thread is running...", "WARNING", MB_ICONEXCLAMATION);
    return 0;
}


int main() {
    MessageBoxA(NULL, "__main__", "WARNING", MB_ICONEXCLAMATION);
    
    HMODULE h = LoadLibraryA("my_dll.dll");
    if (!h) { return 1; }
    hello_fn hello = (hello_fn)GetProcAddress(h, "hello_from_dll");
    
    hello();

    HANDLE hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, NULL);
    if (hThread == NULL) { return 2; }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    FreeLibrary(h);

    MessageBoxA(NULL, "__exit__", "WARNING", MB_ICONEXCLAMATION);
    return 0;
}

