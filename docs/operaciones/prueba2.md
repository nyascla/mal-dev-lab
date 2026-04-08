---
title: "Incidente TFM"
parent: Operaciones 
nav_order: 1
---

# Incidente TFM 

## Descripción del Atacante

En este trabajo no se utiliza un adversario existente ni se replica el comportamiento de un APT conocido. En su lugar, se crea un atacante propio con el fin de construir un escenario didáctico totalmente adaptado a los objetivos del ejercicio. Esto permite ajustar, durante la elaboración del ataque, sus tácticas, técnicas y decisiones operativas para que encajen exactamente con las necesidades formativas del proyecto.

Aunque el adversario no está definido por completo al inicio, el ataque presentado sí constituye un escenario cerrado: la intrusión ya ha ocurrido y todas las evidencias están disponibles para su análisis.

---

## Descripción del Ataque (Resumen Ejecutivo)

El escenario planteado reproduce un ataque estructurado en dos fases, diseñado para simular el comportamiento de un adversario realista. En la fase inicial, el atacante obtiene acceso al equipo víctima mediante un dispositivo físico que le permite ejecutar código de forma inmediata. Con este punto de apoyo establece una conexión remota hacia su infraestructura externa, desde la cual realiza un reconocimiento básico del sistema y prepara la siguiente fase.

En la segunda fase, el adversario despliega su componente principal, diseñado para operar de forma discreta y mantenerse en el sistema sin levantar alertas. Este componente establece persistencia, amplía la capacidad de control del atacante y se integra en procesos legítimos del sistema para dificultar su detección. A partir de este momento, el adversario puede llevar a cabo acciones más avanzadas, como analizar el entorno, escalar privilegios, desplazarse por la red o extraer información.

---

## Mapeo del Ataque a la Cyber Kill Chain y MITRE ATT&CK

En esta sección se presenta una referencia técnica que describe el ataque desde el punto de vista del adversario. Se detalla qué acciones llevó a cabo el atacante, cuáles eran sus objetivos en cada fase y qué técnicas MITRE ATT&CK aplicó. Cada acción se mapea con los artefactos del sistema víctima donde podría encontrarse información relevante sobre dicha actividad, proporcionando una visión clara y útil para el análisis.

La *Cyber Kill Chain* se utiliza como marco para organizar la exposición. El orden elegido es cronológico inverso —del estado final del ataque hacia sus fases iniciales—, ya que este enfoque facilita que el analista comprenda la secuencia real de los hechos: en un escenario DFIR, la investigación siempre comienza desde el impacto final y progresa hacia atrás.

El objetivo de esta sección es ofrecer una guía técnica que relacione de forma directa:

- Las acciones ofensivas del atacante  
- Las técnicas MITRE ATT&CK asociadas  
- Los artefactos del sistema donde podría hallarse evidencia de cada acción  

No se trata de una investigación completa, sino de una referencia estructurada que ayuda a entender cómo se manifiestan las técnicas del atacante en el sistema comprometido.

---

## Acciones sobre el objetivo

### Ransomware

En este punto, el atacante ya ha permanecido un periodo considerable dentro de la organización, llevando a cabo diversas actividades de post-explotación. En la fase final de su operación ejecuta el cifrado de información crítica en el sistema comprometido.

Para una descripción detallada del procedimiento llevado a cabo por el adversario, consúltese el Capítulo correspondiente.

> **Táctica:** Impact (TA0040)  
> **Técnicas:** Data Encrypted for Impact (T1486)  
> **Procedimiento:**  
> Se desplegó un `.NET assembly` dentro del proceso donde residía el implante. Este componente cifró el fichero `documento_importante.txt` utilizando criptografía simétrica. La clave simétrica fue posteriormente cifrada con una clave pública de un esquema asimétrico controlado por el atacante. Finalmente, se dejó una nota de rescate con un correo electrónico de contacto.

**Artefactos relevantes**

- **Sysmon Logs:** Buscar carga de assemblies .NET, creación de procesos anómalos, modificaciones de ficheros y eventos de cifrado o acceso masivo.  
- **Suricata Logs:** Identificar comunicaciones salientes sospechosas.  
- **Event Logs:** Ejecución de binarios, autenticación y errores .NET.  
- **Memory Dump:** Localizar assembly, claves y estructuras del implante.  
- **$MFT$:** Cambios en archivos y timestamps.  
- **$USN Journal$:** Actividad de escritura.  
- **Prefetch:** Ejecución reciente.  
- **Amcache / ShimCache:** Evidencias de ejecución.  
- **.NET CLR Logs:** Carga dinámica de assemblies.  
- **EDR/AV Logs:** Alertas y telemetría.  

---

## Mando y Control (C2)

### Sliver C2

En este punto, el atacante ya dispone de persistencia y controla el sistema mediante un implante de *Sliver*.

> **Táctica:** Defense Evasion (TA0005)  
> **Técnica:** Reflective Code Loading (T1620)  
> **Procedimiento:**  
> La DLL maliciosa usa carga reflexiva (`calibre-launcher.dll`) para conectarse al C2, descargar el implante y ejecutarlo en memoria sin artefactos en disco.

**Artefactos relevantes**

- Sysmon (conexiones, memoria, módulos)  
- Suricata (patrones C2)  
- Event Logs  
- Memory Dump  
- Ausencia en disco (MFT/USN)  
- Prefetch, Amcache, ShimCache  
- EDR/AV  
- Artefactos de red  

---

> **Táctica:** Command and Control (TA0011)  
> **Técnicas:**  
> - Web Protocols (T1071.001)  
> - Encrypted Channel (T1573)  
> **Procedimiento:**  
> Comunicación persistente vía HTTPS con *beaconing*, camuflada como tráfico legítimo y cifrada.

**Artefactos relevantes**

- Sysmon (beaconing)  
- Suricata (JA3, patrones repetitivos)  
- Memory Dump  
- Conexiones persistentes  
- EDR/AV  

---

## Instalación

### Stage 2

El atacante prepara persistencia mediante DLL hijacking y técnicas relacionadas.

> **Táctica:** Defense Evasion (TA0005)  
> **Técnica:** File Permissions Modification (T1222)  
> **Procedimiento:**  
> Copia Calibre a `%LOCALAPPDATA%\Microsoft\WindowsApps` para controlar la carga de DLLs.

**Artefactos relevantes**

- MFT / USN  
- Sysmon  
- Prefetch  
- Amcache / ShimCache  
- Event Logs  

---

> **Táctica:** Execution (TA0002)  
> **Técnica:** Ingress Tool Transfer (T1105)  
> **Procedimiento:**  
> Descarga de `calibre-launcher.dll` maliciosa.

---

> **Táctica:** Defense Evasion / Privilege Escalation  
> **Técnicas:** DLL Hijacking, Masquerading  
> **Procedimiento:**  
> Sustitución de DLL legítima por proxy malicioso.

---

### Persistencia

> **Táctica:** Persistence (TA0003)  
> **Técnica:** Scheduled Task (T1053)  
> **Procedimiento:**  
> Creación de tarea `calibre-update` que ejecuta `calibre-debug.exe`.

---

## Explotación

### Stage 1

> **Tácticas:** Execution / C2  
> **Técnicas:** PowerShell, Reverse Shell, etc.  
> **Procedimiento:**  
> Descarga de archivo `.tmp`, renombrado a `.exe` y ejecución oculta que establece reverse shell.

---

## Entrega

### BadUSB

> **Tácticas:** Initial Access / Execution  
> **Técnicas:** USB, Input Injection  
> **Procedimiento:**  
> Dispositivo HID ejecuta comandos PowerShell automáticamente.

---

## Armamento

Preparación de payloads e infraestructura. Se apoya en análisis preventivo y servicios de detección de C2 como Cobalt Strike.

---

## Reconocimiento

Fase de recopilación de información sobre la organización mediante monitorización externa y análisis de exposición.