#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>


void* get_proc_address(DWORD module_base, DWORD hash_api);

DWORD rol_xor(void* str, int bytes_for_character);

void* get_module_handle(DWORD hash_name);

DWORD runtime_linking(DWORD hash_module, void* hashes, void* destino);



void test_get_proc_address(){
    // KERNEL32_DEF_HASHES:
    //     dd 0x723EB9D5   ; CloseHandle:          
    //     dd 0x46718ae6   ; CreateProcessA:       
    //     dd 0x9590A319   ; ExitProcess:          
    //     dd 0xC8E88006   ; LoadLibraryA:           
    //     dd 0x9e6f6842   ; TerminateProcess:       
    //     dd 0xc547757b   ; WaitForSingleObject:
    //     dd 0xFFFFFFFF    
    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
    printf("\nEXPORTS - kernel32.dll\n");
    printf("CloseHandle: %p\n", get_proc_address((DWORD) hKernel32, 0x723EB9D5));
    printf("CreateProcessA: %p\n", get_proc_address((DWORD) hKernel32, 0x46718ae6));
    printf("ExitProcess: %p\n", get_proc_address((DWORD) hKernel32, 0x9590A319));
    printf("LoadLibraryA: %p\n", get_proc_address((DWORD) hKernel32, 0xC8E88006));
    printf("TerminateProcess: %p\n", get_proc_address((DWORD) hKernel32, 0x9e6f6842));
    printf("WaitForSingleObject: %p\n", get_proc_address((DWORD) hKernel32, 0xc547757b));


    // WS2_32_DEF_HASHES:
    //     dd 0xaff835ad   ; WSACleanup:
    //     dd 0xcebab524   ; WSASocketA:
    //     dd 0xed9ef56d   ; WSAStartup:
    //     dd 0x939d7d9c   ; closesocket:
    //     dd 0xedd8fe8a   ; connect:
    //     dd 0xFFFFFFFF
    HMODULE hWs2 = LoadLibraryA("ws2_32.dll");
    printf("\nEXPORTS - ws2_32.dll\n");
    printf("WSACleanup: %p\n", get_proc_address((DWORD) hWs2, 0xaff835ad));
    printf("WSASocketA: %p\n", get_proc_address((DWORD) hWs2, 0xcebab524));
    printf("WSAStartup: %p\n", get_proc_address((DWORD) hWs2, 0xed9ef56d));
    printf("closesocket: %p\n", get_proc_address((DWORD) hWs2, 0x939d7d9c));
    printf("connect: %p\n", get_proc_address((DWORD) hWs2, 0xedd8fe8a));

}

void test_rol_xor(){
    return;
}

void test_get_module_handle(){
    printf("\nBASE ADDRES\n");
    DWORD kernel32 = 0x4b1ffe8e;
    HMODULE base_addres = get_module_handle(kernel32);
    printf("kernel32.dll: %p\n", base_addres);


    DWORD ws2_32 = 0xd6bc4bcc;
    base_addres = get_module_handle(ws2_32);
    printf("kernel32.dll: %p\n", base_addres);
    return;
}

void test_runtime_linking(){
    return;
}

void main(void) {
    printf("\n__TESTS__\n");

    test_get_module_handle();
    test_get_proc_address();


    test_rol_xor();
    test_runtime_linking();

    printf("\n__TESTS__\n");
    getchar();
}





