# System Monitor (Sysmon)

Event Viewer > Applications and Services Logs > Microsoft > Windows > Sysmon > Operational

## Instalacion

Descarga el paquete Sysmon.zip.
```
https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon
```
Descarga sysmon-config.xml

> NOTA: el repo lleva 4 anyos sin actualizaciones quizas haya que buscar otro
```
https://github.com/SwiftOnSecurity/sysmon-config
```

Poner todo en la misma carpeta ej: `C:\Tools\Sysmon\`

Desde una poweshell como admin

```
.\Sysmon64.exe -accepteula -i sysmonconfig-export.xml
```

Comprobaciones

```
Get-Service Sysmon64
Get-Process Sysmon64
```