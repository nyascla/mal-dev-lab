## KVM on virtualbox

```
sudo rmmod kvm_amd
sudo rmmod kvm
```

## Problems installing ActiveDirectoryDSC module

![alt text](image.png)

https://github.com/Orange-Cyberdefense/GOAD/issues/369

To fix this issue what i did was logged in to the dc with rdp and default credentials that is vagrant:vagrant then change the dns setting in control panel network tab from 127.0.0.1 to Adress automatically

```
flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install --user flathub org.remmina.Remmina
flatpak run --user org.remmina.Remmina
```

```
sudo nmap -sn -PS22,80,443 -PU53,161 192.168.58.0/24
```

1. Abre Panel de control → Redes e Internet → Centro de redes y recursos compartidos
1. A la izquierda: Cambiar configuración del adaptador
1. Botón derecho en tu tarjeta de red (normalmente “Ethernet”) → Propiedades
1. Selecciona Protocolo Internet versión 4 (TCP/IPv4) → Propiedades

```
Unregister-PSRepository -Name "PSGallery"
Register-PSRepository -Default
Get-PSRepository
Install-Module -Name xActiveDirectory -Force -AllowClobber
Install-Module -Name ActiveDirectoryDSC -Force -AllowClobber
```

# Crear usuaio en el dominio

Cambiar el controlador del disco de arranca de SATA a IDE

inslacion sin internet 

```bash
Shift + F10
OOBE\BYPASSNRO
```