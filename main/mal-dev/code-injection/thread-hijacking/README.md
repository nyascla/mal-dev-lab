# Thread Execution Hijacking

https://attack.mitre.org/techniques/T1055/003/

un atacante toma control de un hilo (thread) existente en un proceso en ejecución para insertar y ejecutar código arbitrario.

manipular un hilo vivo sin crear nuevos procesos o hilos

1. Identificación del Objetivo
2. Suspensión del Hilo
3. Inyección de Código
4. Reanudación y Ejecución

Condiciones Necesarias para que un Proceso Modifique el Contexto de un Hilo en Otro Proceso

1. Control de Acceso y Derechos de Handles


> nota: si eres admin puedes modificar el flag de debug y secuentrar un proceso que ya esta en ejecucion



