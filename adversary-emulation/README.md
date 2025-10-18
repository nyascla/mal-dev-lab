# Adversary emulation

Objetivo: Mejorar los procesos y/o las personas de una organizacion

Primer paso: Threat Modelling obtener info (Adversarios y/o ttps)

- top10 ttps (red canary): https://redcanary.com/threat-detection-report/techniques/
- apt modeling (mittre): https://github.com/center-for-threat-informed-defense/adversary_emulation_library
- malpedia: https://malpedia.caad.fkie.fraunhofer.de/families

---

## MITRE (la RAE)

## Atomic red team (ttps aisladas)
- Validating assumptions about security controls (i.e., is my EDR sensor generating the telemetry it is supposed to?)
- Testing detection coverage
- Learning what malicious activity looks like

## Caldera (pruebas automatizadas - semi c2)

“Sandcat”: default agent that receives and executes instructions
“ability”: individual ATT&CK technique
“adversaries”: groups of abilities

You connect the machines you want to test to CALDERA by way of Sandcat. From there you can instruct CALDERA to run a variety of tests on the group of machines you’ve connected to it.

You can build your own agents instead of using Sandcat

## Sliver (c2)

---


## Frameworks post-explotación
- Cobalt Strike (alternativa open source: Sliver)
- Metasploit
- PowerShell Empire: centrado en PowerShell
- Mythic: framework para construir C2s
- Brute Ratel C4: competidor de Cobalt Strike
- Dreadnode IA agents


