---
title: "Ejecutables Windows"
parent: Blogs
nav_order: 1
---

# Ejecutables Windows

¿Alguna vez te has preguntado qué ocurre realmente cuando haces doble clic sobre un fichero ejecutable en Windows?

Detrás de una acción tan simple se esconde una gran cantidad de procesos y mecanismos internos que son fundamentales para entender cómo funciona el sistema operativo. Para responder a esta pregunta, es necesario abordar conceptos clave como:

- El formato **PE32+**  
- La **memoria virtual**  
- La creación de procesos  
- El mapeo de ejecutables en memoria  
- La carga y gestión de DLLs  
- La ejecución de código  

Lo interesante es que todo esto puede surgir de una pregunta tan sencilla —y aparentemente inocente— como:

> *¿Por qué cuando hago doble clic sobre un fichero se abre un programa?*

Esta pregunta, que podría plantear incluso un niño, nos sirve como punto de partida para explorar algunos de los aspectos más importantes sobre **Windows Internals**, que son clave en todo lo relacionado con el malware, tanto desde la perspectiva **Red Team** como **Blue Team**.

En lugar de centrarme en explicaciones puramente teóricas —que puedes encontrar en infinidad de recursos online—, voy a apoyarme en una serie de **proyectos prácticos**. A través de ellos vamos a ver, experimentar y entender cada concepto en profundidad. En mi experiencia, esta es la forma más efectiva de aprender.

A lo largo de esta serie trabajaremos en distintos proyectos:

- **Binary patching**, para comprender en profundidad el formato PE32+ y cómo se estructura un ejecutable en Windows.  
- Un **reflective loader**, que nos permitirá profundizar en cómo Windows mapea y carga ejecutables en memoria.  
- La creación de un **shellcode propio**, diseñado para entender cómo se inicializan procesos a bajo nivel y cómo se cargan bibliotecas del sistema, replicando en ensamblador parte del trabajo que realiza Windows al resolver dependencias y cargar DLLs.

Durante todo el recorrido, iremos conectando estos proyectos con conceptos fundamentales como la **memoria virtual**, el **mapeo de ejecutables**, la **gestión de procesos** y la forma en la que Windows crea, mantiene y administra la ejecución de programas.

---

