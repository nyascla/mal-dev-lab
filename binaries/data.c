// show_entry_runtime.c
#include <stdio.h>
#include <windows.h>
#include <winnt.h>

int main(void) {
    HMODULE base = GetModuleHandle(NULL); // ImageBase real
    if (!base) { fprintf(stderr, "GetModuleHandle failed: %lu\n", (unsigned long)GetLastError()); return 1; }

    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((BYTE*)base + dos->e_lfanew);

    DWORD rva = nt->OptionalHeader.AddressOfEntryPoint;
#if defined(_WIN64)
    unsigned long long preferred = nt->OptionalHeader.ImageBase;
#else
    unsigned long preferred = (unsigned long)nt->OptionalHeader.ImageBase;
#endif

    void *entry_va_runtime = (void*)((BYTE*)base + rva);

    printf("ImageBase (real loaded) : %p\n", (void*)base);
    printf("Preferred ImageBase (header): 0x%llx\n", (unsigned long long)preferred);
    printf("AddressOfEntryPoint (RVA in header): 0x%08x\n", rva);
    printf("EntryPoint VA (calc) = ImageBase_real + RVA : %p\n", entry_va_runtime);

    // Also print pointer at actual header value: preferred + rva (to show difference)
    printf("EntryPoint VA (preferred base + RVA): 0x%llx\n",
           (unsigned long long)(preferred + rva));

    return 0;
}

// C:\Users\test\Desktop\mal-dev-lab\binaries>main.exe
// ImageBase (real loaded) : 00720000
// Preferred ImageBase (header): 0x720000
// AddressOfEntryPoint (RVA in header): 0x000013e4
// EntryPoint VA (calc) = ImageBase_real + RVA : 007213E4
// EntryPoint VA (preferred base + RVA): 0x7213e4