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
}