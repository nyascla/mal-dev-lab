#include <stdio.h>
#include <windows.h>

typedef void (*hello_fn)();

// Función del hilo
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    (void)lpParam; // Evita warning de variable no usada

    MessageBoxA(NULL, "Thread is running...", "INFO", MB_ICONEXCLAMATION);
    return 0;
}

// Función para cargar DLL y obtener la función deseada
hello_fn LoadHelloFunction(const char *dll_name, const char *func_name, HMODULE *out_module) {
    if (!dll_name || !func_name || !out_module) {
        return NULL;
    }

    *out_module = LoadLibraryA(dll_name);
    if (!*out_module) {
        fprintf(stderr, "Error: No se pudo cargar DLL '%s'\n", dll_name);
        return NULL;
    }

    hello_fn func = (hello_fn)GetProcAddress(*out_module, func_name);
    if (!func) {
        fprintf(stderr, "Error: No se pudo encontrar función '%s' en DLL '%s'\n", func_name, dll_name);
        FreeLibrary(*out_module);
        *out_module = NULL;
    }

    return func;
}

int main(void) {
    MessageBoxA(NULL, "__main__", "INFO", MB_ICONEXCLAMATION);

    HMODULE dll_handle = NULL;
    hello_fn hello = LoadHelloFunction("my_dll.dll", "hello_from_dll", &dll_handle);

    if (!hello) {
        return EXIT_FAILURE;
    }

    // Llamar a la función desde la DLL
    hello();

    HANDLE thread_handle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);

    WaitForSingleObject(thread_handle, INFINITE);

    CloseHandle(thread_handle);

    FreeLibrary(dll_handle);

    MessageBoxA(NULL, "__exit__", "INFO", MB_ICONEXCLAMATION);
    return EXIT_SUCCESS;
}
