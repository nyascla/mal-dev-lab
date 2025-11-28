## Install ".NET SDK"

wget https://packages.microsoft.com/config/debian/13/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
rm packages-microsoft-prod.deb

sudo apt-get update && sudo apt-get install -y dotnet-sdk-10.0

```bash
dotnet --version
```

## .NET Assemblies (C# o VB.NET)

> NOTA: El Ecosistema "Sharp"
> - SharpHound: El recolector de datos de BloodHound.
> - SharpSploit: Una biblioteca de técnicas ofensivas en C#.
> - Rubeus: La herramienta de referencia para ataques de Kerberos.

## CLR (Common Language Runtime) de .NET

El CLR es el motor de ejecución de .NET que viene incluido en todas las versiones de Windows. El CLR permite cargar y ejecutar assemblies .NET directamente desde bytes en memoria sin necesidad de que exista un archivo .exe o .dll en disco.

### .exe vs .dll

mejor dll mas pequenyo y puedes elegir que funcion ejecutar


dotnet new console -n RedTeam

## Developing
```
dotnet publish -c Release -r win-x64 --self-contained true
```

- --self-contained: anyade o no el clr en el propio ejecutable
