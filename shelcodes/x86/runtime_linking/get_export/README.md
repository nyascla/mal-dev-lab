``` scss
BaseDll (dirección base del módulo)
 └── 0x3C [últimos 4 bytes Primera sección] -> Offset to NtHeaders
       └── 
             └── 
 └── Saltar a NtHeaders
       └── Offset 0x78 desde el inicio de NT Headers -> Offset to IMAGE_EXPORT_DIRECTORY 
             └── 
			 
 └── Saltar a IMAGE_EXPORT_DIRECTORY
       └── [0x0C] -> NumberOfNames
```


## _IMAGE_EXPORT_DIRECTORY
```c
pub struct IMAGE_EXPORT_DIRECTORY {
	/* 00h */ DWORD Characteristics;      
	/* 04h */ DWORD TimeDateStamp;        // Marca temporal de compilación
	/* 08h */ WORD  MajorVersion;
	/* 0Ah */ WORD  MinorVersion;

	/* 0Ch */ DWORD Name;                 // RVA -> string ASCII con el nombre de la DLL
	/* 10h */ DWORD Base;                 // Ordinal base (primer número de ordinal)

	/* 14h */ DWORD NumberOfFunctions;    // Tamaño de AddressOfFunctions[]
	/* 18h */ DWORD NumberOfNames;        // Tamaño de AddressOfNames[] y AddressOfNameOrdinals[]

	/* 1Ch */ DWORD AddressOfFunctions;   // RVA -> DWORD[NumberOfFunctions]
	                                      // Cada DWORD es un RVA a la función exportada

	/* 20h */ DWORD AddressOfNames;       // RVA -> DWORD[NumberOfNames]
	                                      // Cada DWORD es un RVA a un string con el nombre de la función

	/* 24h */ DWORD AddressOfNameOrdinals;// RVA -> WORD[NumberOfNames]
	                                      // Cada WORD es el ordinal de la función
};

```