# BYOVD

Un driver es un programa de software que permite que el sistema operativo se comunique con un dispositivo de hardware

Se almacenan generalmente en:
- C:\Windows\System32\drivers → archivos `.sys` principales del kernel.

También hay controladores en forma de DLL, INF u otros archivos de instalación en:

- C:\Windows\inf
- C:\Windows\System32\DriverStore

Drivers de espacio de usuario: se ejecutan en el espacio del usuario, menos privilegiados, más seguros.

Drivers de espacio de kernel: se ejecutan en el kernel, tienen acceso directo al hardware y a la memoria, pero un fallo puede bloquear el sistema.

OALabs
[Vulnerable Antivirus Driver Used by Ransomware - We Reverse Engineer How!!?](https://www.youtube.com/watch?v=ViWLMfSwGVA)


