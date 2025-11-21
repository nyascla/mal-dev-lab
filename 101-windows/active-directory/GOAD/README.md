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

# Unir un host al dominio

```powershell
# El cliente debe usar como DNS → el DC de NORTH (WINTERFELL)
New-NetIPAddress -InterfaceAlias "Ethernet" -IPAddress 192.168.56.50 -PrefixLength 24 -DefaultGateway 192.168.56.1
Set-DnsClientServerAddress -InterfaceAlias "Ethernet" -ServerAddresses 192.168.56.11

# Verificar que todo está bien
Get-DnsClientServerAddress
nslookup NORTH.SEVENKINGDOMS.LOCAL

# Activar windows PRO: VK7JG-NPHTM-C97JM-9MPGT-3V66T

# Unir el host al dominio (user: north\Administrator password: NgtI75cKV+Pu)
# Option 1
Add-Computer -DomainName north.sevenkingdoms.local -Credential north\Administrator -Restart

# Option 2: Windows + R: sysdm.cpl
```

user: jon.snow
password: iknownothing

# GOAD-Light

- domain : `sevenkingdoms.local`
    - kingslanding : DC01 running on Windows Server 2019 (with windefender enabled by default)
- domain : `north.sevenkingdoms.local`
    - winterfell : DC02 running on Windows Server 2019 (with windefender enabled by default)
    - castelblack : SRV02 running on Windows Server 2019 (with windefender disabled by default)

![alt text](./GOAD-Light_schema.png)

