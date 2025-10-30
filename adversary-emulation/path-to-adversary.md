> Distinguir entre dos proyectos:
> - Simulacion de adversarios
> - Desarrollo malware
>

# Malware

Crear nuestro agente de adversary emulation

Creación de modulos de desarrollo propio, diseñados para ejecutarse en 
los sistemas de los clientes con el fin de recopilar información sobre su nivel 
de protección.

C2 dual que permita, por un lado, el control técnico de los implantes 
desplegados en los endpoints del cliente, y por otro, ofrecer una interfaz 
visual accesible para el cliente

## Modulos
- [Ransomware]("./ransomware.md")
- [EDR-killing]("./edr-killing.md")
- [Beaconing]("./beaconing.md")
- [Exfiltracion]("./exfiltrar.md")
---
- [Movimiento lateral]("./movimiento-lateral.md")
- [Escalada de privilegios]("./escalada-privilegios.md")


## C2 (One ``panel`` to rule them all)
- [c2]("./c2.md")

## Alcance
> Que es y que no es el proyecto?

Poner a prueva a los proveedores, ver de que son capaces o no nuestras herramientas:
- Tests para emular comportamientos maliciosos

Relacionar con el equipo de thread hunting:
- Por ejemplo el equipo de thread hunting ve en un reporte de un post incidente una tecnica que han utilizado para vulnerar una emprea
- somos nosotras capaces de detectar ese caso?
- Ejecutar un test muy concreto para responder a la pregunta de podemos detectar esto?

Entrenar al equipo de IR

## Niveles de Sigilo

Concepto interno para el proyecto, trabajar con distintos niveles de ruido:

- BAJO (*Elefante*): Desarrollo basico, no se tiene en cuenta las protecciones de la victima
- MEDIO (*Caballo*): Podria NO ser detectado en equipos con una seguridad basica pero un equipo bien protegido lo deberia detectar
- ALTO (*Gato*): nivel maximo de “stealthy”

---

## Proyectos disponibles post-explotacion

> El objetivo de esta seccion es investigar el estado del arte.

Agente post-explotacion: cualquier software instalado en la víctima que ejecuta tareas de forma autónoma.

### Agentes
- Mittre caldera
- Sliver
- Cobalt strike
- Dreadnode

### Herramientas
- Atomic Red Team: test muy concretos con el objetivo de realizar actividades mapeadas a Mitre attack
    - https://www.atomicredteam.io/atomic-red-team
- Metasploit 
- PurpleSharp
- Infection Monkey
- nishang: https://github.com/samratashok/nishang
- hidden-tear: https://github.com/utkusen/hidden-tear
- mimikatz: https://github.com/gentilkiwi/mimikatz

---

## Fases

### Fases 0 (Introduccion)

Módulo Ransomware Basico

Contenido:
1. Recorrer sistema de ficheros
1. Encriptación de archivos con una librería estándar (ej. AES con clave hardcodeada).
1. Módulo de "rescate" para revertir la encriptación durante las pruebas.

Ojetivos:
1. Establecer la línea base de detección de los EDR.
1. Validar el entorno de desarrollo y pruebas.

### Fases 1

Módulo C2/Beaconing Basico

Contenido:
1. Establecer conexión periódica (beacon) a un C2 sobre un protocolo claro (ej. HTTP/S plano).
1. Implementar un loop básico de `check-in -> get-task -> execute -> post-result`.
1. Ejecutar comandos simples (`whoami`, `hostname`).
1. Exfiltrar la salida de los comandos al C2.

Ojetivos:
1. Probar la detección basada en red (firmas de tráfico, JA3, etc.).
1. Construir la infraestructura básica.


### Fases 2

Módulo de Exfiltración Baico

Contenido:
1.  **Recolección:** Búsqueda y recolección de archivos de interés en el sistema de ficheros (ej. por extensión: `.pdf`, `.docx`, `.xlsx`).
1.  **Empaquetado:** Compresión de los datos recolectados en un único archivo (ej. ZIP) para facilitar la transferencia.
1.  **Transferencia:** Envío del archivo empaquetado al servidor C2

Objetivos:
1.  Evaluar la detección de anomalías en el tráfico de red (grandes volúmenes de datos salientes).
1.  Validar la capacidad del C2 para recibir y reconstruir grandes ficheros.

### Fases 3 (MVP - Integración)

Integración de Módulos

Contenido:
1.  **Refactorización del Agente:**

Objetivos:
1.  Tener un agente funcional (MVP) que combine varias capacidades.
2.  Superar las defensas basadas en firmas y análisis estático simple.
3.  Evaluar la telemetría generada y las detecciones conductuales del EDR.

### Fases 4 (EDR Bypass)

EDR Bypass

Proceso iterativo para mejorar el sigilo del agente:
-   **Evasión de Hooks:** Implementar llamadas directas o indirectas a syscalls (`direct-syscalls`, `indirect-syscalls`).
-   **Inyección de Procesos:** Mover la ejecución de tareas a procesos legítimos (`process-injection`).
-   **Manipulación de Memoria:** Cargar y ejecutar herramientas en memoria (BOFs, Reflective DLLs).
-   **Comunicación Encubierta:** Usar protocolos de C2 no estándar o domain fronting.

---

C2 donde enviar logs
Almacenamiento de logs en local (cifrado a poder ser)
Enumeración del equipo > Enumeración de red
Movimiento lateral / Persistencia
Ransomware
Exfiltración (no datos reales)