conseguimos cargar la dll en un proceso y conseguirmos ejecutar las funciones maliciosas de la dll

- loadlibrary
- loadlibraryex
- ldrloaddll
- manual mapping

dll callbacks

- dll_process_attach
- dll_process_detach
- dll_thread_attach
- dll_thread_detach

para cargar una dll en otro proceso buscares la direccion de memoria de load library en el proceso objetivo

kernel32 se carga en todos los procesos en la misma direccion de memoria

por ejemplo con createremotethread podemos crear un hilo en el proceso objetivo que ejecute loadlibrary y cargue la dll maliciosa

https://www.youtube.com/watch?v=RasdnQmM3IY