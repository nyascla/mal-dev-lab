Process Injection

inyectar algo que queremos que se ejecute en el proceso objetivo

## hollowing

objetivo tipico svchost.exe 

1. CREATE PROCES 
    - <https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessa>
2. BUSCAMOS SU PEB del proceso hijo
    - NtQueryInformationProcess (http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FProcess%2FNtQueryInformationProcess.html)
        - IMAGE BASE
        - RVA AL ENTRY POINT
3. PONEMOS EN EL ENTRY POINT EL SHELLCODE
4. REANUDAMOS EJECUCION

> Una version mas interesante de esto es pasar un PE entero con secciones + reloc + ...