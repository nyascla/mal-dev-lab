# Malware Development Lab

> *PoCs didácticas creadas por mí para explicar TTPs de malware*

## Estructura

### [shellcodes](./shellcodes/)       
    - x86 y x64 ABI
    – PIC, runtime linking, import hashes
    - remote shell
    - mitigacion: EATF

### [syscalls](./syscalls/)           
    - x86 vs x64 syscalls
    – win32-api, native-api, direct-syscalls, indirect-syscalls

### [binaries](./binaries/)           
    – patching: jmp, entry point, IAT
    - mitigacion: ASLR, DEP

### [processes](./processes/)         
    – process hollowing, process injection, masquerading
    - mitigacion: CFG

### [dlls](./dlls/)                  
    - injection, hijacking   
    – DLL reflection, reflective loaders

recopilacion de lolbins y tecnicas de persistencia y anti-analisis
<br>
<br>
<br>
<br>

# 🚧 Under Construction 🚧

### [C2](./C2/)                       – PoCs (infraestructura)
### [anti-analysis](./anti-analysis/) – PoCs (borrado de evidencias, anti sandbox)
### [persistence](./persistence/)