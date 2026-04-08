---
title: Inicio
nav_order: 0
---

# 🛡️ All Things Cybersecurity

Bienvenido a **All Things Cybersecurity**, un espacio dedicado al estudio práctico de la ciberseguridad desde el enfoque de la **simulación de adversarios (Adversary Simulation)**.

Este blog está diseñado con un propósito principalmente **didáctico**, donde se documentan técnicas, procedimientos y laboratorios orientados a comprender el comportamiento real de un atacante y mejorar la capacidad de análisis y defensa.

---

## 🧩 CTF Educacional

Como punto de partida de este proyecto, se diseñó y desarrolló un **CTF educacional** como Trabajo de Fin de Máster. Este reto fue concebido no solo como una prueba técnica, sino como un escenario didáctico completo orientado a la **simulación realista de un ciberataque**, documentando de forma exhaustiva cada una de sus fases.

El objetivo del trabajo es proporcionar un entorno que permita a analistas de ciberseguridad mejorar sus capacidades de **detección, análisis e investigación**, mediante la comprensión integral del ciclo de vida de un ataque. A través de este enfoque, el proyecto busca aproximar al analista a la mentalidad del atacante, facilitando la interpretación de evidencias desde una perspectiva ofensiva y defensiva.

El resultado final consiste en un conjunto de **artefactos forenses** generados en sistemas comprometidos, que sirven como base para ejercicios prácticos de análisis forense (enfoque **blue team**). Estos artefactos permiten estudiar la huella dejada por el ataque y reconstruir los eventos ocurridos en el sistema.

Para generar este material, el núcleo del trabajo se centra en:

- La concepción, diseño y desarrollo de un ciberataque realista  
- La ejecución controlada del ataque en un entorno de laboratorio  
- La documentación completa del proceso ofensivo  
- La recopilación de evidencias y artefactos generados durante la intrusión  
- El análisis posterior de dichos artefactos desde una perspectiva forense  

De este modo, el usuario que analice el material no solo podrá estudiar la infección desde el punto de vista defensivo, sino también comprender el **cómo** y el **porqué** detrás de cada artefacto encontrado, mejorando así su capacidad de correlación, detección y respuesta ante amenazas reales.

Todo el contenido asociado al CTF, incluyendo enunciado, resolución detallada, explicación técnica del ataque, desarrollo de payloads, ubicación de artefactos y evidencias, se encuentra disponible en el repositorio del proyecto:

👉 https://github.com/nyascla/All-Things-Cybersecurity/blob/main/latex/release/main.pdf

Este contenido está publicado bajo una **licencia MIT**, lo que permite su uso, modificación y distribución de forma libre, siempre que se mantenga la atribución correspondiente al autor original.

---

## 🎯 Objetivo

El objetivo principal es:

- Aprender ciberseguridad de forma práctica  
- Simular escenarios reales de ataque en entornos controlados  
- Analizar cada etapa de un incidente de seguridad  
- Documentar técnicas, herramientas y artefactos generados  

Este trabajo se sitúa dentro del ámbito de la simulación de adversarios, una metodología que permite evaluar tanto la eficacia de los sistemas de defensa como las capacidades del personal ante incidentes de seguridad.

En este contexto, el enfoque principal no es ofensivo en sí mismo, sino **formativo**: recrear escenarios realistas para practicar la detección, el análisis y la interpretación de actividades maliciosas.

---

## 🧭 Estructura del contenido

El contenido del blog se organiza en varias secciones:

### 🔴 Operaciones
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

### 🛠️ Técnicas
Aquí se estudian **técnicas específicas en profundidad**, incluyendo:

- Descripción teórica
- Implementación práctica (PoC)
- Ejecución controlada
- Recolección de artefactos
- Análisis de evidencias generadas

Esta sección está orientada a entender el *cómo* y el *por qué* detrás de cada técnica.

---

### 🧪 Laboratorio
En esta sección se documentan:

- Entornos de prueba
- Herramientas utilizadas
- Configuraciones
- Procedimientos experimentales

Sirve como base para reproducir los escenarios descritos en otras secciones.

---

### 🧠 Windows Internals
Sección teórica centrada en conceptos internos del sistema operativo Windows, fundamentales para comprender técnicas avanzadas.

Algunos temas incluyen:

- Estructura de ejecutables PE
- PEB (Process Environment Block)
- TEB (Thread Environment Block)
- Tabla de módulos cargados
- Carga de DLLs
- Mecanismos internos del sistema

---

## 🧩 Enfoque

Todo el contenido está orientado a:

- Simulación realista de ataques en entornos controlados  
- Documentación reproducible  
- Análisis técnico profundo  
- Relación entre teoría y práctica  

---

## 📌 Navegación

Utiliza el menú lateral para explorar las distintas secciones del blog:

- **Operaciones** → escenarios completos  
- **Técnicas** → técnicas individuales y PoCs  
- **Laboratorio** → herramientas y entornos  
- **Windows Internals** → fundamentos teóricos  

---

## 🚀 Nota final

Este blog no busca únicamente listar información, sino construir una base de conocimiento práctica que permita entender cómo opera un adversario y cómo se puede detectar y analizar su actividad de manera efectiva.