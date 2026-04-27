---
title: "Viaje al centro de la máquina"
parent: Blogs
nav_order: 3 
---

## Introducción

Esta sección está destinada a analistas que no estén familiarizados con conceptos de memoria y explotación de bajo nivel. Se presenta un repaso de los fundamentos necesarios para entender este tipo de ataques.

---

## Componentes básicos

Existe una relación fundamental entre:

- **Disco**
- **Memoria RAM**
- **CPU**

### Disco
- Almacena datos **persistentes**.
- Contiene archivos que **no están en uso activo**.

### RAM
- Memoria **volátil** donde se cargan los datos en uso.
- Para ejecutar un programa, sus datos deben cargarse desde disco a RAM.

### CPU
- Ejecuta instrucciones.
- Accede a la RAM mediante **direcciones de memoria**.

---

## Direcciones de memoria

Cuando la CPU quiere leer un dato, solicita:

> “Dame el contenido en la dirección X”

El tamaño de estas direcciones depende de la arquitectura:

| Arquitectura | Bits dirección | RAM máxima teórica |
|-------------|--------------|--------------------|
| 32 bits     | 32 bits      | 2³² ≈ 4 GB         |
| 64 bits     | 64 bits      | 2⁶⁴ ≈ 18 EB        |

### Nota práctica
- Los sistemas actuales suelen usar **48 bits efectivos**.
- Esto permite hasta **256 TB de RAM**.

---

## Organización de la RAM

- La memoria se organiza como **direcciones contiguas**.
- El **sistema operativo** y la **CPU** gestionan qué datos hay en cada dirección.

---

## Paginación

La memoria se divide en **páginas**:

- Tamaño típico: **4 KB**
- 4 KB = 4096 bytes = 2¹²

### Estructura de una dirección

```
[47 ... 12] → Número de página (36 bits)
[11 ... 0] → Offset (12 bits dentro de la página)
```


---

## MMU (Memory Management Unit)

- Componente de la CPU encargado de:
  - Traducir direcciones
  - Gestionar permisos

### Funcionamiento

- Usa los **bits superiores** → localizar la página (page table)
- Usa los **bits inferiores** → acceder al byte exacto dentro de la página

---

## Espacio de memoria de un proceso

```
Dirección alta
0xFFFFFFFFFFFFFFFF
┌─────────────────────┐
│ KERNEL │ ← Solo accesible por el SO
├─────────────────────┤
│ STACK │ ← Crece hacia abajo ↓
│ │ Variables locales, return addresses
│ │
│ (espacio) │
│ │
│ HEAP │ ← Crece hacia arriba ↑
│ │ malloc(), new()
├─────────────────────┤
│ BSS │ ← Globales no inicializadas
├─────────────────────┤
│ DATA │ ← Globales inicializadas
├─────────────────────┤
│ TEXT │ ← Código ejecutable (solo lectura)
├─────────────────────┤
0x0000000000000000
Dirección baja
```

---

## Userland vs Kernel

- **Userland**:
  - Espacio donde se ejecutan los programas de usuario
  - Acceso restringido

- **Kernel**:
  - Núcleo del sistema operativo
  - Control total del sistema

### Interacción
- Los programas no acceden directamente al kernel.
- Se comunican mediante **syscalls (llamadas al sistema)**.

---

## Idea clave

- La memoria es un espacio organizado y protegido.
- La CPU, el sistema operativo y la MMU trabajan juntos para:
  - Traducir direcciones
  - Controlar accesos
  - Mantener aislamiento entre procesos