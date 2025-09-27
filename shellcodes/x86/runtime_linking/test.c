#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#include <intrin.h>



void* get_proc_address(DWORD module_base, DWORD hash_api);
DWORD rol_xor(void* str, int bytes_for_character);
void* get_module_handle(DWORD hash_name);
DWORD runtime_linking(DWORD hash_module, void* hashes, void* destino);


extern int asm_add(int a, int b);   // C verá asm_add, linker busca _asm_add


int main(void) {
    printf("<=== __INIT__TEST__ ===>\n");
    printf("%d\n", asm_add(3,4));

    // HMODULE hKernel32 = LoadLibraryA("kernell32.dll");
    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");

    HMODULE hWs2 = LoadLibraryA("ws2_32.dll");

    // __debugbreak();  // provoca un breakpoint     __asm { int 3 }

    DWORD k = (DWORD)hKernel32;
    DWORD hash = 0x723EB9D5;

    printf("hKernel32: %d\n", k);


    void* f = get_proc_address((DWORD) hKernel32, hash);

    printf("CloseHandle: %p\n", f);
    getchar();
    return 0;
}

// KERNEL32_DEF_HASHES:
//     dd 0x723EB9D5   ; CloseHandle:          
//     dd 0x46718AE6   ; CreateProcessA:       
//     dd 0x9590A319   ; ExitProcess:          
//     dd 0xC8E88006   ; LoadLibraryA:           
//     dd 0x9e6f6842   ; TerminateProcess:       
//     dd 0xc547757b   ; WaitForSingleObject:
//     dd 0xFFFFFFFF    


// WS2_32_DEF_HASHES:
//     dd 0xaff835ad   ; WSACleanup:
//     dd 0x8b9d756a   ; WSASocket:
//     dd 0xed9ef56d   ; WSAStartup:
//     dd 0x939d7d9c   ; closesocket:
//     dd 0xedd8fe8a   ; connect:
//     dd 0xFFFFFFFF
