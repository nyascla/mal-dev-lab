# LoadLibrary Implementation

[ReflectiveDLLInjection](https://github.com/stephenfewer/ReflectiveDLLInjection)

``` bash
make && make run
```

## Pasos

1. Cargar el PE en memoria.
1. Leer las cabeceras.
1. Reservar memoria en el proceso para la DLL.
1. Copiar las cabeceras al nuevo espacio reservado.
1. Cargar las secciones del PE en memoria hacia la nueva memoria reservada.
1. Resolver importaciones y parchear la IAT.
1. Llamar a la función DllMain.