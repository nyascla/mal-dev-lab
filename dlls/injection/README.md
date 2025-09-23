https://www.youtube.com/watch?v=RasdnQmM3IY

# LoadLibrary Method

1. Obtener acceso al proceso objetivo

    - Conseguir un handler con permisos necesarios

2. Ejecutar LoadLibrary en el proceso objetivo

    - Reservar memoria en el proceso para la ruta de la DLL
    - Escribir la ruta de la DLL en la memoria reservada
    - Crear un hilo remoto que ejecute LoadLibrary apuntando a la DLL
