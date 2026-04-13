# Reflective Injection

- [ReflectiveDLLInjection](https://github.com/stephenfewer/ReflectiveDLLInjection)
- [donut](https://github.com/TheWover/donut)

## Pasos

La ejecución se transfiere (usando CreateRemoteThread() o un pequeño código inicial) a la función ReflectiveLoader de la librería.

Como la librería está cargada en una posición aleatoria de la memoria, esta función primero calcula dónde está ubicada para poder leer su propia información interna.

Después, busca dentro de kernel32.dll las direcciones de tres funciones importantes:

LoadLibraryA
GetProcAddress
VirtualAlloc

Luego, reserva un bloque de memoria nuevo donde va a copiar su propia librería (la ubicación exacta no importa).

A continuación:

Copia las cabeceras y secciones de la librería a esa nueva memoria.
Resuelve las dependencias, cargando otras librerías necesarias y obteniendo las direcciones de sus funciones.
Ajusta las direcciones internas (relocaciones) para que todo funcione correctamente en la nueva ubicación.

Cuando todo está listo, ejecuta la función principal de la librería (DllMain) indicando que el proceso se ha adjuntado.

Finalmente:

La librería ya queda cargada en memoria.
El control vuelve al código inicial que llamó al loader, o el hilo termina si se usó CreateRemoteThread().