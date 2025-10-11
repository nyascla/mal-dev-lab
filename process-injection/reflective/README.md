
https://github.com/stephenfewer/ReflectiveDLLInjection

| reflective_dll.dll | inject.exe | victim |

1. Hacer llegar el PE reflective_dll.dll a la memoria de la victima
2. Consegur ejecutar ReflectiveLoader() [CreateRemoteThread(), tiny bootstrap shellcode]
3. Resolver funcionas:
    - Calculate its own image's current location
    - Parse its own headers
    - Parse kernel32.dll export (LoadLibraryA, GetProcAddress and VirtualAlloc)
4. Allocate a continuous region of memory into which it will proceed to load its own image


## Partes

### Paso-1
- Codigo que abra un handle al proceso objetivo:
    - Reserve un chunk de memoria
    - Copie el PE de una dll
    - cree un hilo en el proceso victipa CreateRemoteThread() y ejecute una funcion de la dll copiada

### Paso-2
- Tener metodo ReflectiveLoader() que revuelva:
    - Su base addres
    - Obtenga informacion de sus headers (no se cual :/)
    - que obtenga las funciones

### Paso-3
- Desde una dll copiar el PE de una dll y arreglar las relocaciones y arrancar la dll 


---


1. ReflectiveLoader will first calculate its own image's current location in memory so as to be able to parse its own headers for use later on

2. The ReflectiveLoader will then parse the host processes kernel32.dll export table in order to calculate the addresses of three functions required by the loader, namely:
    - LoadLibraryA, GetProcAddress and VirtualAlloc.

3. The ReflectiveLoader will now allocate a continuous region of memory into which it will proceed to load its own image. The location is not important as the loader will correctly relocate the image later on.

4. The library's headers and sections are loaded into their new locations in memory.


5.  The ReflectiveLoader will then process the newly loaded copy of its image's import table, loading any additional library's and resolving their respective imported function addresses.

6. The ReflectiveLoader will then process the newly loaded copy of its image's relocation table.

7. The ReflectiveLoader will then call its newly loaded image's entry point function, DllMain with DLL_PROCESS_ATTACH. The library has now been successfully loaded into memory.

8. Finally the ReflectiveLoader will return execution to the initial bootstrap shellcode which called it, or if it was called via CreateRemoteThread, the thread will terminate.

---
