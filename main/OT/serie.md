## Linux

### Ver qué dispositivos USB están conectados

``` bash
lsusb                          # Lista simple y rápida (lo que más usas)
lsusb -v                       # Mucho más detalle (verbose)
lsusb -t                       # Vista en árbol (muy útil para ver jerarquía)
lsusb -d 0403:6001             # Filtra por Vendor:Product ID (ejemplo FTDI)
```

### Ver qué pasó cuando conectaste algo (logs del kernel)

``` bash
dmesg | tail -n 40             # Últimas líneas → casi siempre muestra el dispositivo nuevo
dmesg | grep -i usb            # Solo mensajes relacionados con USB
dmesg | grep tty               # Muy útil para puertos serie (ttyUSB*, ttyACM*)
```

### Ver permisos y propietario/grupo actual de un dispositivo

``` bash
ls -l /dev/ttyUSB0             # Ejemplo clásico
ls -l /dev/bus/usb/001/005     # Dispositivo USB puro (bus 001, dispositivo 005)
```