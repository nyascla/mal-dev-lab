# GOAD

https://github.com/Orange-Cyberdefense/GOAD

~/.goad/.venv

```bash
vmware --version
vagrant --version
vagrant plugin list
```

```
./goad.sh -t check -l GOAD-Light -p virtualbox
./goad.sh -t install -l GOAD-Light -p virtualbox
```

# Unir un usuaio a `NORTH.SEVENKINGDOMS.LOCAL`


```powershell
# El cliente debe usar como DNS → el DC de NORTH (WINTERFELL)
New-NetIPAddress -InterfaceAlias "Ethernet" -IPAddress 192.168.56.50 -PrefixLength 24 -DefaultGateway 192.168.56.1
Set-DnsClientServerAddress -InterfaceAlias "Ethernet" -ServerAddresses 192.168.56.11

# Opción DHCP (si funciona en tu lab)
# ipconfig /renew

# Verificar que todo está bien
Get-DnsClientServerAddress
ping NORTH.SEVENKINGDOMS.LOCAL
nslookup NORTH.SEVENKINGDOMS.LOCAL

# Unir al dominio
$cred = Get-Credential north\Administrator
Add-Computer -DomainName north.sevenkingdoms.local -Credential $cred -Restart
NgtI75cKV+Pu

# 1. Escribe aquí la contraseña en texto plano (es un laboratorio, no pasa nada)
$pass = ConvertTo-SecureString "NgtI75cKV+Pu" -AsPlainText -Force

# 2. Crea el objeto de credencial manualmente
$cred = New-Object System.Management.Automation.PSCredential ("north\Administrator", $pass)

# 3. Ejecuta el comando usando esa credencial creada
Add-Computer -DomainName north.sevenkingdoms.local -Credential $cred -Restart

VK7JG-NPHTM-C97JM-9MPGT-3V66T
```

# GOAD-Light

- domain : `sevenkingdoms.local`
    - kingslanding : DC01 running on Windows Server 2019 (with windefender enabled by default)
- domain : `north.sevenkingdoms.local`
    - winterfell : DC02 running on Windows Server 2019 (with windefender enabled by default)
    - castelblack : SRV02 running on Windows Server 2019 (with windefender disabled by default)

![alt text](./GOAD-Light_schema.png)

