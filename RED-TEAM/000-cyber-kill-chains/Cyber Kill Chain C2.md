Conseguimos ejecucion de codigo

- camapanyas de phishing
- vulnerabilidades
- identidad

post-explotacion

cada vez mas dificil droppear exe por la profilicacion de edr
    - un nuevo procesos que realice acciones sospechosas saltara muchas alarmas

el objetivo sera dropear el codigo malicioso dentro de un  proceso de confianza
    - las acciones del malware se mezclaran con las acciones del proceso legitimo y vamos a tener mas posibilidades de sobrevivir

para inyectar nuestro codigo en memoria
- module stomping
- reflective dll injection
- early bird apc
- entry point injection
- thread hijacking
- COM hijacking
- WMI Event subscription
- **DLL Hijacking**

side loading o activation context hijack

utilizamos call stack spoofing para ocular la ejecucion del implante