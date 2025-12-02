- ``regsvr32.exe``: Ejecutar scripts/COM objects sin dejar binario en disco
- ``rundll32.exe``: Cargar DLL maliciosas y ejecutar funciones exportadas
- ``certutil.exe``: escargar ficheros desde HTTP/HTTPS
- ``wmic.exe``: Enumeración remota, ejecución de procesos WMI
- ``schtasks.exe``: Crear tareas programadas como persistencia
- ``reg.exe``: Modificar claves de registro, persistencia
- ``tasklist.exe``: Enumerar procesos de seguridad
- ``taskkill.exe``: Terminar procesos de seguridad

The threat actor activated Windows’ Secondary Logon service to enable the runas command – a built-in Windows feature that allows running programs under different user credentials.