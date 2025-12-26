# .NET SDK

- `RID (Runtime Identifier)`: En qué sistema operativo y arquitectura exacta quieres que funcione tu aplicación
    - dotnet publish -c Release -r win-x64
    - TFM (Target Framework Moniker): `<TargetFramework>net9.0-windows</TargetFramework>`
        - Habilitar APIs dependientes de Windows desde el fichero `.csproj`

- `Self-contained`: Mete todo el .NET Runtime dentro de tu .exe o carpeta de publicación
    - --self-contained true
    - --self-contained false


> - dotnet build: Compilar para desarrollo, rápido y simple
> - dotnet publish: Genera la versión final preparada para ejecutarse y distribuirse
> - dotnet --list-runtimes

## Building Assemblis

> NOTA: (.exe vs .dll) mejor dll mas pequenyo y puedes elegir que funcion ejecutar

Crear un proyecto: 

``` bash
dotnet new console -o ExeBasico --framework net9.0
cd ExeBasico
```

## .DLL Basica

``` bash
dotnet new classlib -o MiniDll -f net9.0
dotnet new console -o Loader -f net9.0
```

``` bash
dotnet build -c Release
```

Compilamos los dos proyectos, los ponemos en la misma ruta para que el ejecutable encuentre la dll y ejecutamos con `dotnet Loader.dll`

En .NET actual, el programa real siempre es un DLL. En Windows se genera además un EXE, que es solo un pequeño lanzador que ejecuta ese DLL. En Linux ese lanzador no se crea, así que solo obtienes el DLL, que ejecutas con dotnet archivo.dll.

> `Loader.exe` → pequeño wrapper && `Loader.dll` → programa real

Para hacer que el Loader fuere un exe desde Linux:

``` bash
dotnet publish -c Release -r win-x64 --self-contained false
```

## .EXE Basico (.exe single-file self-contained)

``` bash
dotnet publish -c Release -r win-x64 \
    --self-contained true \
    -p:PublishSingleFile=true \
    -p:IncludeNativeLibrariesForSelfExtract=true \
    -p:PublishReadyToRun=false
```

*Error en WINE*:

Un `.exe single-file self-contained` contiene un stub nativo (escrito en C++) al principio del .exe, este:

- Descomprime el runtime en memoria o en una carpeta temporal
- Lanza el CoreCLR real
- El CoreCLR ejecuta el IL (Intermediate Language)

Wine reconoce la cabecera PE32+, intenta ejecutar el stub… pero el stub de .NET 9 está compilado con características muy nuevas de Windows (APIs de Windows 10/11, formato de compresión específico, etc.) que Wine todavía no soporta.

## Problemas cross-compiling 

Desde Linux hacia Windows con .NET:

1. No se genera .exe al compilar con dotnet build
1. Las Windows API no están disponibles en Linux
    - Si tu código usa cosas como: System.Windows.Forms
    - La compilación puede fallar, esas referencias solo existen en Windows o requieren -windows en el TFM (net9.0-windows).
1. Dependencias que requieren build nativo no funcionan
    - Paquetes como: `Costura.Fody`, `DllExport`
    - Pueden fallar porque necesitan herramientas de Windows (MSVC, cl.exe).
1. NativeAOT NO funciona en cross-OS
    ``` xml
    <PropertyGroup>
    <PublishAot>true</PublishAot>
    </PropertyGroup>
    ```
    - Obtendrás: Cross-OS native compilation is not supported.

### Buenas prácticas

- Usar únicamente APIs cross-platform siempre que sea posible.
- Para compatibilidad Windows, usar TFM
    ``` xml
    <TargetFramework>net9.0-windows</TargetFramework>
    ```
- Para generar EXE real → usar siempre
    ``` powershell
    dotnet publish -c Release -r win-x64
    ```
- Evitar paquetes que compilan código nativo.

