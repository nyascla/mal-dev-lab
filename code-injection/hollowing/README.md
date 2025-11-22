# Process Hollowing

## Pasos

1. Creamos un proceso suspendido
    - <https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessa>
2. Conseguir el Entrypoint del proceso hijo
    - Llegar al PEB con NtQueryInformationProcess 
        - (http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FProcess%2FNtQueryInformationProcess.html)
    - Conseguir el Base Addres
    - Desde las cabeceras PE conseguir su Entrypoint
3. PONEMOS EN EL ENTRY POINT EL SHELLCODE
4. REANUDAMOS EJECUCION

> Una version mas interesante de esto es pasar un PE entero con secciones + reloc + ...

## Walking PE to AddressOfEntryPoint

1. _IMAGE_DOS_HEADER 
    - offset 0x3c = DWORD e_lfanew
2. _IMAGE_NT_HEADERS = (BaseAddres + e_lfanew)
    - offset 0x18 = _IMAGE_OPTIONAL_HEADER
3. _IMAGE_OPTIONAL_HEADER
    - offset 0x10 = DWORD AddressOfEntryPoint

*objetivo tipico svchost.exe *