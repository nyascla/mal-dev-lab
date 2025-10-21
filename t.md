> Distinguir entre dos proyectos:
> - Simulacion de adversarios
> - Desarrollo malware
>
> Los modulos malware se pueden utilizar en la simulacion de adversario o pueden 
ser stand-alone

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
- [Exfiltracion]("./exfiltrar.md")
- [Movimiento lateral]("./movimiento-lateral.md")
- [Persistencia]("./persistencia.md")
- [Escalada de privilegios]("./escalada-privilegios.md")
- [Asignación remota de tareas]()

## C2 (One ``panel`` to rule them all)
- [c2]("./c2.md")

## Alcance
> Que es y que no es el proyecto?

Poner a prueva a los proveedores, ver de que son capaces o no nuestras herramientas
    - Tests para emular comportamientos maliciosos

Relacionar con el equipo de thread hunting
    - Por ejemplo el equipo de thread hunting ve en un reporte de un post incidente una tecnica que han utilizado para vulnerar una emprea
    - somos nosotras capaces de detectar ese caso?
    - Ejecutar un test muy concreto para responder a la pregunta de podemos detectar esto?

Entrenar al equipo de IR

Red team vs Adversary emulation
    - precio
    - esto pueden ser ejecuciones recurrentes

## Niveles de Sigilo

Concepto interno para el proyecto, trabajar con distintos niveles de ruido:

- BAJO (*Elefante*): Desarrollo basico, no se tiene en cuenta las protecciones de la victima
- MEDIO (*Caballo*): Podria NO ser detectado en equipos con una seguridad basica pero un equipo bien protegido lo deberia detectar
- ALTO (*Gato*): nivel maximo de “stealthy”

---

## Proyectos post-explotacion

> El objetivo de esta seccion es investigar el estado del arte.

Agente post-explotacion: cualquier software instalado en la víctima que ejecuta tareas de forma autónoma.

### Agentes
- Mittre caldera
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
Durante todas las fases se profundizara en como las soluciones EDR

### Fases 0 (MVP)
Modulo Ransomware basico 
### Fases 1
### Fases 2
### Fases 3


