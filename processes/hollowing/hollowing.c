#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef NTSTATUS(NTAPI* pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

// typedef struct _PROCESS_BASIC_INFORMATION {
//     PVOID Reserved1;
//     PPEB PebBaseAddress; // <- Aquí está el PEB
//     PVOID Reserved2[2];
//     ULONG_PTR UniqueProcessId;
//     PVOID Reserved3;
// } PROCESS_BASIC_INFORMATION;

int main(void) {
    STARTUPINFOW si = {0};          // Estructura para configurar hijo
    PROCESS_INFORMATION pi = {0};   // Cuando llamas a CreateProcessW, Windows rellena esta estructura
    si.cb = sizeof(si);             // Windows lo utiliza para saber qué versión de la estructura le estás pasando

    LPCWSTR app = L".\\calc.exe";
    BOOL result = 
        CreateProcessW(
            app,           // lpApplicationName
            NULL,          // lpCommandLine
            NULL, NULL,    // lpProcessAttributes, lpThreadAttributes
            FALSE,         // bInheritHandles
            CREATE_SUSPENDED, // dwCreationFlags -> hilo principal creado suspendido
            NULL,          // lpEnvironment
            NULL,          // lpCurrentDirectory
            &si,
            &pi
        );

    if (!result) { // Si devuevle una valor mayor a 0 hay un error
        wprintf(L"CreateProcessW failed: %u\n", GetLastError());
        return 1;
    }



    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pNtQueryInformationProcess NtQueryInformationProcess =
        (pNtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) {
        printf("No se pudo obtener NtQueryInformationProcess\n");
        return 1;
    }

    PROCESS_BASIC_INFORMATION pbi;
    ULONG retLen;
    NTSTATUS status = NtQueryInformationProcess(pi.hProcess,
                                  ProcessBasicInformation,
                                  &pbi,
                                  sizeof(pbi),
                                  &retLen);

    if (status != 0) {
        printf("Error NtQueryInformationProcess: 0x%lx\n", status);
        return 1;
    }

    printf("PEB del proceso: %p\n", pbi.PebBaseAddress);

    // Leer ImageBaseAddress del PEB
    PEB peb;
    SIZE_T bytesRead;
    if (ReadProcessMemory(pi.hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), &bytesRead)) {
        printf("ImageBaseAddress: %d\n", peb.BeingDebugged);
    } else {
        printf("No se pudo leer PEB\n");
    }


    ResumeThread(pi.hThread);

    getchar();

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}
