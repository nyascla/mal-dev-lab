---
title: Inicio
nav_order: 0
---

# 🛡️ All Things Cybersecurity

Bienvenido a All Things Cybersecurity, un blog que nace como un recurso didáctico, orientado a la formación de equipos de ciberseguridad y basado en una idea fundamental: la mejor forma de aprender es haciendo.

La metodología utilizada se apoya en la simulación de adversarios (Adversary Simulation), un enfoque que permite comprender en profundidad cómo se diseñan, construyen, ejecutan y analizan los ataques reales. Cada contenido recorre el ciclo completo: desde el diseño inicial del ataque y la creación desde cero de los payloads, junto con la base teórica necesaria para entender su funcionamiento, hasta el despliegue de la infraestructura y la ejecución.

A partir de ahí, el enfoque evoluciona hacia la perspectiva Blue Team, abordando la detección del ataque, la identificación y recolección de artefactos relevantes, y su posterior análisis. El blog pone especial énfasis en las técnicas más relevantes del marco MITRE ATT&CK, centrando el aprendizaje en entenderlas de forma integral: desde su creación hasta su detección e investigación.

El objetivo es proporcionar una visión completa y práctica que permita no solo reproducir técnicas, sino comprenderlas en profundidad y aplicarlas en entornos reales de defensa.

---

## CTFs

Como parte de los recursos disponibles en este blog, se ofrece un CTF educacional desarrollado como Trabajo de Fin de Máster, titulado “Simulación realista de adversarios como herramienta formativa para DFIR y Blue Team”. Este reto se plantea como una opción formativa práctica para aquellos que deseen entrenar sus habilidades de análisis a partir de artefactos reales generados durante un ciberataque.

El CTF se basa en la recreación de una kill chain completa, en la que se diseña, implementa y ejecuta un ataque en un entorno controlado. Todo el proceso ha sido documentado en detalle, incluyendo el diseño del ataque, la creación de payloads, la preparación de la infraestructura y la ejecución de cada fase.

Como resultado, se ponen a disposición del usuario los artefactos generados durante la ejecución del ataque, junto con una explicación detallada de las técnicas utilizadas y la justificación de las decisiones tomadas. Esto permite a los analistas no solo practicar sus capacidades de análisis y detección, sino también entender el contexto completo en el que se generan dichas evidencias.

De este modo, el CTF se convierte en un recurso especialmente útil para la formación de equipos de ciberseguridad, permitiendo trabajar sobre escenarios realistas y mejorar las habilidades de DFIR y Blue Team desde una perspectiva práctica.

Todo el contenido —incluyendo artefactos, documentación técnica y resolución detallada— está disponible para su descarga:

👉 https://github.com/nyascla/All-Things-Cybersecurity/blob/main/latex/release/main.pdf

Este material se distribuye bajo licencia MIT, facilitando su uso, adaptación y reutilización con fines formativos.

---

## Estructura del contenido

El contenido del blog se organiza en varias secciones:

### Blog
Esta sección actúa como puerta de entrada a los conceptos del blog, ofreciendo contenidos más accesibles que introducen al lector en distintas áreas de la ciberseguridad.

A través de escenarios, ejemplos prácticos y preguntas guiadas, los artículos plantean el contexto necesario para entender cómo funcionan determinadas técnicas o conceptos. Desde aquí, se referencia de forma estructurada a las entradas más técnicas del blog, donde se desarrolla en profundidad cada uno de los temas tratados.

El objetivo de esta sección es proporcionar una visión clara e intuitiva, permitiendo al lector construir una base sólida antes de profundizar en los aspectos más avanzados. De este modo, se conecta la teoría con la práctica, facilitando una comprensión progresiva y estructurada del contenido.

---

### Laboratorio
En esta sección se documentan:

- Entornos de prueba
- Herramientas utilizadas
- Configuraciones
- Procedimientos experimentales

Sirve como base para reproducir los escenarios descritos en otras secciones.

---

### Operaciones
En esta sección se desarrollan **kill chains completas**, simulando escenarios de ataque de extremo a extremo.

- Reconocimiento
- Acceso inicial
- Ejecución
- Persistencia
- Escalada de privilegios
- Movimiento lateral
- Exfiltración

El objetivo es entender cómo se encadenan las técnicas en un ataque real.

---

### Técnicas
Aquí se estudian **técnicas específicas en profundidad**, incluyendo:

- Descripción teórica
- Implementación práctica (PoC)
- Ejecución controlada
- Recolección de artefactos
- Análisis de evidencias generadas

Esta sección está orientada a entender el *cómo* y el *por qué* detrás de cada técnica.

---



### Windows Internals
Sección teórica centrada en conceptos internos del sistema operativo Windows, fundamentales para comprender técnicas avanzadas.

Algunos temas incluyen:

- Estructura de ejecutables PE
- PEB (Process Environment Block)
- TEB (Thread Environment Block)
- Tabla de módulos cargados
- Carga de DLLs
- Mecanismos internos del sistema

---