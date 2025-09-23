#include <windows.h>
#include <stdio.h>
#include <wchar.h>


// Función para obtener el PEB en x64
DWORD_PTR GetCurrentPeb() {
    return __readgsqword(0x60); // x64: GS:[0x60]
}

// Función para leer un puntero desde una dirección
DWORD_PTR ReadPointer(DWORD_PTR address) {
    return *(DWORD_PTR*)address;
}

// Función para leer un DWORD desde una dirección
DWORD ReadDword(DWORD_PTR address) {
    return *(DWORD*)address;
}

// Función para leer un WORD desde una dirección
WORD ReadWord(DWORD_PTR address) {
    return *(WORD*)address;
}

// Función para mostrar todos los módulos usando offsets directos
void ListLoadedModules(DWORD_PTR pLdr) {
    printf("=== MODULOS CARGADOS ===\n");
    // PEB_LDR_DATA->InLoadOrderModuleList offset en x64: 0x10
    DWORD_PTR listHead = pLdr + 0x10;               // list[0] cada posicion contiene una direccion de memoria
    DWORD_PTR firstEntry = ReadPointer(listHead);   // Direccion del primer _LDR_DATA_TABLE_ENTRY

    DWORD_PTR currentEntry = firstEntry;
    do {
        DWORD_PTR dllBase = ReadPointer(currentEntry + 0x30);  // DllBase
        DWORD_PTR nameOffset = currentEntry + 0x58;            // BaseDllName
        DWORD_PTR nameBuffer = ReadPointer(nameOffset + 0x8);  // Buffer
        
        wprintf(L"%s - 0x%p\n", (wchar_t*)nameBuffer, (void*)dllBase);

        currentEntry = ReadPointer(currentEntry);
    } while (currentEntry != firstEntry);
}

// Función para mostrar información básica del PEB
DWORD_PTR ShowPebInfo() {
    DWORD_PTR pPeb = GetCurrentPeb();

    if (pPeb == 0) {
        printf("No se pudo obtener el PEB\n");
        return 0;
    }
    
    printf("=== INFORMACION BASICA DEL PEB ===\n");
    printf("PEB Address: 0x%p\n", (void*)pPeb);
    
    // PEB->ImageBaseAddress offset en x64: 0x10
    DWORD_PTR imageBase = ReadPointer(pPeb + 0x10);
    printf("ImageBaseAddress: 0x%p\n", (void*)imageBase);
    
    // PEB->BeingDebugged offset en x64: 0x02
    BYTE beingDebugged = *(BYTE*)(pPeb + 0x02);
    printf("BeingDebugged: %d\n", beingDebugged);
    
    // PEB->Ldr offset en x64: 0x18
    DWORD_PTR ldr = ReadPointer(pPeb + 0x18);
    printf("Ldr: 0x%p\n", (void*)ldr);
    
    return ldr;
}

int main() {
    printf("Enumer Modulos(x64)\n");
    
    // Mostramos información básica del PEB
    DWORD_PTR pLdr = ShowPebInfo();

    // Listamos todos los módulos cargados
    ListLoadedModules(pLdr);

    return 0;
}