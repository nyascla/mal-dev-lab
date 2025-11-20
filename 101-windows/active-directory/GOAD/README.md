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
Add-Computer -DomainName "NORTH.SEVENKINGDOMS.LOCAL" -Credential "NORTH\eddard.stark" -Restart
FightP3aceAndHonor!.
Add-Computer -DomainName "NORTH.SEVENKINGDOMS.LOCAL" -Credential ".\Administrator" -Restart
NgtI75cKV+Pu 


```

# GOAD-Light

- domain : `sevenkingdoms.local`
    - kingslanding : DC01 running on Windows Server 2019 (with windefender enabled by default)
- domain : `north.sevenkingdoms.local`
    - winterfell : DC02 running on Windows Server 2019 (with windefender enabled by default)
    - castelblack : SRV02 running on Windows Server 2019 (with windefender disabled by default)

![alt text](./GOAD-Light_schema.png)

