# PEB (Process Environment Block)

Estructura interna de Windows no definida, Windows no proporciona una struct oficial y esta puede cambiar entre builds. 

Solo en modo usuario y está asociado a cada proceso individual.

Informacion importarte que podemos encontrar en el PEB:
- ImageBaseAddress
- BeingDebugged
- Ldr (PEB_LDR_DATA)

La forma más fácil de ver esta estructura es desde windbg.

```bash
# Ver PEB
dt _PEB @$peb
# Ver _PEB_LDR_DATA
dx @$peb->Ldr
dt _PEB_LDR_DATA <direccion>
# Ver _LDR_DATA_TABLE_ENTRY
dt _LDR_DATA_TABLE_ENTRY @esi
dx @$peb->Ldr->InLoadOrderModuleList.Flink
dt _LDR_DATA_TABLE_ENTRY <direccion>
# Ver nombre del modulo
dt _UNICODE_STRING @esi+0x2c
```

## x86 Ver Modulos Cargados en el proceso 

### _PEB
![alt text](./img/image.png)
### _PEB_LDR_DATA
![alt text](./img/image-1.png)
### _LIST_ENTRY
![alt text](./img/image-2.png)
### _LDR_DATA_TABLE_ENTRY
![alt text](./img/image-3.png)
## _UNICODE_STRING
![alt text](image.png)

## x64 Ver Modulos Cargados en el proceso 
