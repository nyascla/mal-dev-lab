#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int main() {
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    
    if (hKernel32 == NULL) {
        printf("Error: No se pudo obtener kernel32.dll\n");
        return 1;
    }
    
    BYTE* baseAddress = (BYTE*)hKernel32;
    DWORD peOffset = *(DWORD*)(baseAddress + 0x3C);
    DWORD offset = peOffset + 0x88;

    // Offset
    DWORD* fieldAddress = (DWORD*)(baseAddress + offset);
    DWORD fieldValue = *fieldAddress;
    printf("Direccion del offset: 0x%p\n", fieldAddress);
    printf("Valor del offset: 0x%08X\n", fieldValue);

    DWORD peOffset = *(DWORD*)(baseAddress + fieldValue);


    return 0;
}