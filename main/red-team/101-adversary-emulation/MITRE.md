# MITRE

## MITRE ATT&CK
- https://attack.mitre.org/

## MITRE Engenuity ATT&CK® Evaluations
- Ejercicios de Adversary emulation sobre los principales prveedores de seguridad: https://evals.mitre.org/

## MITRE Engenuity Center for Threat-Informed Defense
- Colleccion de TTPs de muchos grupos apt: https://github.com/center-for-threat-informed-defense/adversary_emulation_library

## MITRE Attack Flow
- ficheros para visualizar flujos sobre ataques: https://github.com/center-for-threat-informed-defense/attack-flow
    - Lista de ejemplos de flows: https://github.com/center-for-threat-informed-defense/attack-flow/tree/main/corpus
    - Herramienta para visualizacion: https://center-for-threat-informed-defense.github.io/attack-flow/ui/

# Mittre ATT&CK® Deep Dive:

https://www.youtube.com/watch?v=Kmq9TFXdkg4&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK

En el mundo del adversary simulation el vocabulario lo define attack

- ``Tácticas``(El PARA QUÉ): 

    ¿Para qué está haciendo esto?

    Es el objetivo táctico o la meta intermedia del adversario en una fase del ataque. Responde a la pregunta: ¿Para qué está haciendo esto?

    Ejemplo: Acceso Inicial, Robo de Credenciales, Exfiltración de Datos.

- ``Técnicas``(El QUÉ): 

    ¿Qué está haciendo para lograr su objetivo?

    Es el método específico que utiliza el adversario para conseguir el objetivo de la táctica. Responde a la pregunta:     - 

    Ejemplo: Phishing, Inyección de Procesos, Uso de PowerShell

- ``Procedimientos``(El CÓMO): 

    Es la implementación concreta de una técnica. Describe los pasos exactos, las herramientas, el malware y la configuración específica. Es la "huella digital" única del atacante o del grupo.    

    Ejemplo: La implementación de la técnica de Phishing sería: enviar un email con el asunto "Factura Urgente", adjuntando un archivo Word con una macro específica que ejecuta un comando de PowerShell ofuscado para descargar un payload de http://servidor-malicioso.com/implante.exe.


## Privilege Escalation
https://www.youtube.com/watch?v=PwKerlyhPUM&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=2

## Defense Evasion
https://www.youtube.com/watch?v=WmJcbDfy9L4&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=3

## Persistence
https://www.youtube.com/watch?v=BhMurf3Ydvc&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=4

## Process Injection
https://www.youtube.com/watch?v=CwglaQRejio&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=5

## Lateral Movement
1. https://www.youtube.com/watch?v=nICBXnzWL10&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=7
2. https://www.youtube.com/watch?v=M6MvhxKe80Q&list=PL92eUXSF717W-CLRsq4zgYdlvBHhtiALK&index=6