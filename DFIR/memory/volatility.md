## VirtualBox

```bash
VBoxManage controlvm "<NombreVM>" pause
VBoxManage debugvm "<NombreVM>" dumpvmcore --filename mem.raw
VBoxManage controlvm "<NombreVM>" resume
```

## VMware

VMware crea dumps de memoria cuando se genera un snapshot con memoria incluida.

Crear snapshot (obligatorio marcar “Snapshot the virtual machine’s memory”):