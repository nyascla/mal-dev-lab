#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>


void* get_proc_address(DWORD module_base, DWORD hash_api);
void* get_module_handle(DWORD hash_name);
DWORD multi_import(HMODULE module_base, void* ptr_source, void* ptr_dest);


void test_get_proc_address(HMODULE hKernel32, HMODULE hWs2){
    // KERNEL32_DEF_HASHES:
    //     dd 0x723EB9D5   ; CloseHandle:          
    //     dd 0x46718ae6   ; CreateProcessA:       
    //     dd 0x9590A319   ; ExitProcess:          
    //     dd 0xC8E88006   ; LoadLibraryA:           
    //     dd 0x9e6f6842   ; TerminateProcess:       
    //     dd 0xc547757b   ; WaitForSingleObject:
    //     dd 0xFFFFFFFF    
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
    printf("\nEXPORTS - ws2_32.dll\n");
    printf("WSACleanup: %p\n", get_proc_address((DWORD) hWs2, 0xaff835ad));
    printf("WSASocketA: %p\n", get_proc_address((DWORD) hWs2, 0xcebab524));
    printf("WSAStartup: %p\n", get_proc_address((DWORD) hWs2, 0xed9ef56d));
    printf("closesocket: %p\n", get_proc_address((DWORD) hWs2, 0x939d7d9c));
    printf("connect: %p\n", get_proc_address((DWORD) hWs2, 0xedd8fe8a));

}

void test_get_module_handle(){
    printf("\nBASE ADDRES\n");
    DWORD kernel32 = 0x4b1ffe8e;
    HMODULE base_addres = get_module_handle(kernel32);
    printf("kernel32.dll: %p\n", base_addres);


    DWORD ws2_32 = 0xd6bc4bcc;
    base_addres = get_module_handle(ws2_32);
    printf("ws2_32.dll: %p\n", base_addres);
    return;
}

void test_multi_import(HMODULE hKernel32, HMODULE hWs2){
    printf("\nMULTI IMPORT\n");
    
    printf("kernel32.dll\n");
    const char *array_strings[] = {
        "CloseHandle",
        "CreateProcessA",
    };

    #define SIZE 2
    uint32_t ptr_source[SIZE + 1] = {0x723EB9D5, 0x46718ae6, 0xFFFFFFFF};
    uint32_t ptr_dest[SIZE];

    DWORD x =  multi_import(hKernel32, ptr_source, ptr_dest);
    
    for (int i = 0; i < SIZE; i++) {
        printf("%s: %p\n", array_strings[i], ptr_dest[i]);
    }

    printf("hWs2.dll\n");
    const char *array_strings1[] = {
        "WSACleanup",
        "WSASocketA",
    };

    uint32_t ptr_source1[SIZE + 1] = {0xaff835ad, 0xcebab524, 0xFFFFFFFF};
    uint32_t ptr_dest1[SIZE];

    x =  multi_import(hWs2, ptr_source1, ptr_dest1);
    
    for (int i = 0; i < SIZE; i++) {
        printf("%s: %p\n", array_strings1[i], ptr_dest1[i]);
    }

}

void main(void) {
    printf("\n__TESTS__\n");

    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
    HMODULE hWs2 = LoadLibraryA("ws2_32.dll");

    test_get_module_handle();
    test_get_proc_address(hKernel32, hWs2);
    test_multi_import(hKernel32, hWs2);


    printf("\n__TESTS__\n");
    getchar();
}





