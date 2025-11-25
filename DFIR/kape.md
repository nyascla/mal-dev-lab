# KAPE - Kroll Artifact Parser and Extractor

https://github.com/EricZimmerman/KapeFiles

## Sync

Busca y sincroniza nuevos Targets y Modules del repositorio oficial.
```bash
kape.exe --sync
```

También puede utilizarse el script de actualización incluido:
```bash
Get-KAPEUpdate.ps1
```
## `.tkape` files

Los archivos Target KAPE (.tkape) definen qué artefactos deben recolectarse y cómo deben copiarse. Incluyen rutas, variables dinámicas, exclusiones y prioridades. Los Targets determinan la fase de adquisición.

## `.mkape` files

Los archivos Module KAPE (.mkape) definen acciones a ejecutar sobre la evidencia, normalmente scripts o herramientas externas que procesan los artefactos previamente extraídos. Suelen utilizar ejecutables de la suite de Eric Zimmerman, PowerShell u otras utilidades forenses.

## Examples

```bash
kape.exe --tsource C: --target RegistryHives --tdest "C:\Users\test\Documents\kape" --vhdx Demo --vss
```

- `--tsource`: Especifica la fuente de adquisición (ruta local, unidad física o recurso remoto).
- `--target`: Lista de .tkape a ejecutar.
- `--tdest`: Directorio donde se almacenará la evidencia recopilada.
- `--vhdx <nombre>`: Genera un contenedor VHDX con la salida del proceso.
    - La evidencia se empaqueta primero como ZIP y, tras descomprimirse, se obtiene un .vhdx montable directamente en el sistema.
- `--vss`: Incluye datos provenientes de Volume Shadow Copies.
    - Un Volume Shadow Copy es un snapshot de nivel volumen que permite acceder a versiones anteriores de archivos y estructuras NTFS.

KAPE realiza primero una pasada copiando los artefactos que puede extraer mediante acceso estándar al sistema de archivos. Posteriormente ejecuta una segunda pasada (Deferred) para aquellos artefactos que requieren acceso RAW al disco.

## GUI

Los comandos tambien se puedes crear desde la interfaz grafica 