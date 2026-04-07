# CFG (Control Flow Guard) 

Restringe las llamadas a funciones mediante una lista de destinos válidos predefinidos.

Comprobar en tiempo de ejecución que cada salto indirecto (por ejemplo a través de un puntero a función, call eax, etc.) apunta a una dirección marcada como destino válido.

```
cl /guard:cf main.c 

```

```
/link  /guard:cf
```

## _IMAGE_OPTIONAL_HEADER.DllCharacteristics

![alt text](image.png)

## Ejemplo

> En la seccion de Binary patching hay un ejemplo donde se ve la mitigacion en accion

[patching](../../binaries\entrypoint)

```
Win + R
eventvwr.msc
Windows Logs → Application
Buscar el error concreto
Click derecho (Event Properties)
```

```
Exception code: 0xc0000409
```

![alt text](image-1.png)