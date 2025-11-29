# .NET

.NET es una plataforma de desarrollo creada por Microsoft
- Se puede desarrollar y hacer build en Linux, macOS y Windows
- Se pueden ejecutar las aplicaciones en Linux, macOS y Windows

## Componentes

- `.NET Runtime`: "motor" que ejecuta las aplicaciones.
    - Es el sucesor evolucionado del CLR
        - `CLR` (Common Language Runtime) de .NET: El motor de ejecución del .NET Framework antiguo (Windows only)
- `.NET SDK`" “paquete de herramientas” para desarrollar
    - El compilador (roslyn)
    - Las librerías base (.NET Runtime + ...)
    - La herramienta de línea de comandos dotnet
    - Dentro vienen varios “workloads” que puedes instalar o no:
        - `aspnetcore` (viene por defecto): ASP.NET Core (web y APIs)
        - `maui`: .NET MAUI (apps móviles y escritorio multiplataforma)
        - `wasm`: WebAssembly (Blazor WebAssembly)
        - `windowsdesktop` WinForms y WPF (apps clásicas de Windows)


## Install ".NET SDK"

`Linux`:

``` bash
wget https://packages.microsoft.com/config/debian/13/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
rm packages-microsoft-prod.deb
sudo apt-get update && sudo apt-get install -y dotnet-sdk-10.0
```
`Windows`: siguiente > siguiente
```bash
dotnet --version
```

## .NET Assemblies

Un `.NET assembly` es el archivo `.exe` o `.dll` que sale cuando compilas con `dotnet build` o `dotnet publish`.

El código C# compilado a `IL` (Intermediate Language) que entiende el .NET Runtime (parecido al bytecode de Java).

```
IL (Intermediate Language) + metadatos + manifest
```

## El Ecosistema "Sharp"

- `SharpHound`: El recolector de datos de BloodHound.
- `SharpSploit`: Una biblioteca de técnicas ofensivas en C#.
- `Rubeus`: La herramienta de referencia para ataques de Kerberos.