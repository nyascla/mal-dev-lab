¿Tienes curiosidad por el mundo del malware y por entender cómo funciona la tecnología a bajo nivel?

He publicado un post titulado:

# ¿Qué ocurre cuando se hace doble clic sobre un programa en Windows?

## Introducción a los fundamentos del desarrollo de malware

Puedes leerlo aquí:
https://nyascla.github.io/All-Things-Cybersecurity/blogs/ejecutables.html

Y este es el blog completo:
https://nyascla.github.io/All-Things-Cybersecurity/

En él, a través de 3 proyectos prácticos, puedes entender en profundidad todo lo que sucede desde que haces doble clic en un programa hasta que este está listo para ser utilizado por el usuario, al mismo tiempo que aprendes los conceptos clave para el desarrollo y análisis de malware.

Los proyectos son:

* **Binary patching**: parchear un binario ya compilado para comprender en profundidad el formato **PE32+** y cómo se estructura un ejecutable en Windows.
* **Reflective loader**: cargar una DLL dentro de un proceso de forma manual, sin utilizar las bibliotecas de Windows, lo que permite profundizar en cómo el sistema mapea y carga ejecutables en memoria.
* **Shellcode propio**: desarrollo de un blob de código ensamblador que invoca un MessageBox, con el objetivo de entender en detalle cómo se ejecuta código a bajo nivel sin el soporte de un ejecutable convencional.
  A través de este proyecto se explora cómo interactúa el shellcode con las bibliotecas del sistema (resolución manual de APIs, carga de librerías y llamadas a funciones), cómo se representa y organiza un proceso en memoria (secciones, layout, permisos), y cuál es la relación directa con la memoria virtual.
  Además, se analizan aspectos clave como los permisos de memoria (RX, RWX), las diferencias entre arquitecturas de 32 y 64 bits y las implicaciones que esto tiene en la ejecución del código, el uso de registros y el *calling convention*.

Después de realizar y comprender estos tres proyectos, tendrás los conocimientos fundamentales para el desarrollo y análisis de malware.

Y, de paso, estarás preparado para el día en que alguien te pregunte:
“¿Por qué, cuando hago doble clic sobre un icono del escritorio, el ordenador hace cosas?”

Y puedas dar la explicación más larga, técnica y soporífera que cualquier persona no técnica jamás querría escuchar.

#WindowsInternals #Cybersecurity #ReverseEngineering #MalwareAnalysis #LowLevel #Programming
