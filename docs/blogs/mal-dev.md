---
title: "Ejecutables Windows"
parent: Blogs
nav_order: 1
---

# ¿Qué ocurre cuando se hace doble clic sobre un programa en Windows?  
## Introducción a los fundamentos del desarrollo de malware

En esta entrada responderemos a la pregunta del título a través de tres proyectos prácticos y aprenderemos los conceptos fundamentales de *Windows Internals* necesarios para desarrollar y analizar malware.

Los conceptos que abordaremos serán:

- El formato **PE32+**  
- La **memoria virtual**  
- La creación de procesos y el mapeo de ejecutables en memoria  
- Cómo es un proceso en memoria  
- La carga y gestión de **DLLs**  
- La ejecución de código  

Los proyectos consistirán en:

* **Binary patching**: parchear un binario ya compilado para comprender en profundidad el formato **PE32+** y cómo se estructura un ejecutable en Windows.
* **Reflective loader**: cargar una DLL dentro de un proceso de forma manual, sin utilizar las bibliotecas de Windows, lo que permite profundizar en cómo el sistema mapea y carga ejecutables en memoria.
* **Shellcode propio**: desarrollo de un blob de código ensamblador que invoca un MessageBox, con el objetivo de entender en detalle cómo se ejecuta código a bajo nivel sin el soporte de un ejecutable convencional.
A través de este proyecto se explora cómo interactúa el shellcode con las bibliotecas del sistema (resolución manual de APIs, carga de librerías y llamadas a funciones), cómo se representa y organiza un proceso en memoria (secciones, layout, permisos), y cuál es la relación directa con la memoria virtual.
Además, se analizan aspectos clave como los permisos de memoria (RX, RWX), las diferencias entre arquitecturas de 32 y 64 bits, y las implicaciones que esto tiene en la ejecución del código, el uso de registros y el calling convention.

Después de realizar y comprender estos tres proyectos, tendrás los conocimientos fundamentales para el desarrollo y análisis de malware. Y, de paso, estarás preparado para el día en que alguien te pregunte: “¿Por qué, cuando hago doble clic sobre un icono del escritorio, el ordenador hace cosas?”, y puedas dar la explicación más larga, técnica y soporífera que cualquier persona no técnica jamás querría escuchar.


---

## Binary patching

En este proyecto parcheamos el *entry point* de un programa para que ejecute primero nuestro *shellcode* y, posteriormente, continúe con la ejecución normal del programa.

Para el ejemplo se utiliza un *shellcode* desarrollado por mí que abre un **MessageBox**.

🔗 Proyecto:  
https://github.com/nyascla/All-Things-Cybersecurity/tree/main/main/mal-dev/binary-patching/entrypoint

Como recurso adicional, incluyo un pequeño programa en C que imprime toda la información de un fichero PE. Esto permite visualizar los *offsets* de cada sección y entender en detalle la estructura interna de un ejecutable en Windows.

🔗 Recursos sobre PE:  
https://github.com/nyascla/All-Things-Cybersecurity/tree/main/main/windows-internals/pe-files

---

## Reflective loader

El primer paso es entender cómo Windows crea procesos y carga DLLs en memoria. Para ello, es recomendable revisar los siguientes documentos de referencia:

🔗 Documentación:  
https://github.com/nyascla/All-Things-Cybersecurity/blob/main/main/windows-internals/windows-loader/process-loader.md
https://github.com/nyascla/All-Things-Cybersecurity/blob/main/main/windows-internals/windows-loader/dll-loader.md

A continuación, se desarrolla un proyecto donde se implementa una versión propia de `LoadLibrary`, lo que permite cargar DLLs en memoria sin utilizar la función proporcionada por Windows.

🔗 Implementación de loader:  
https://github.com/nyascla/All-Things-Cybersecurity/tree/main/main/windows-internals/windows-loader/my-dll-loader

Finalmente, se construye un *reflective loader* completo, mediante el cual se carga una DLL en un proceso objetivo (*proceso víctima*) sin necesidad de escribirla en disco. Esto permite ejecutar código sin utilizar los mecanismos estándar del sistema.

🔗 Reflective injection:  
https://github.com/nyascla/All-Things-Cybersecurity/tree/main/main/mal-dev/code-injection/reflective-injection

---

## Shellcode propio

Para este proyecto recomiendo comenzar con el *shellcode* que ejecuta un **MessageBox**, ya que es más sencillo y didáctico y hay versiones tanto para 32 bits como para 64 bits.

No obstante, si te interesa profundizar más, en el mismo repositorio también se incluye una *reverse shell* en 64 bits, más avanzada y orientada a escenarios reales de bajo nivel.

🔗 Shellcodes:  
https://github.com/nyascla/All-Things-Cybersecurity/tree/main/main/mal-dev/101-code/ASM-x86_64
