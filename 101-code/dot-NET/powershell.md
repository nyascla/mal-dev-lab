# PowerShell = .NET + Shell

- PowerShell ejecuta comandos que devuelven objetos .NET, no texto plano.
- Cada comando (cmdlet) es en realidad una clase .NET escrita en C# (o en cualquier lenguaje .NET).

## C# directamente dentro de PowerShell

PowerShell permite escribir código C# inline usando Add-Type.

```powershell
Add-Type @"
using System;
public class Saludo {
    public static void Hola(string nombre) {
        Console.WriteLine("Hola, " + nombre + "!");
    }
}
"@

[Saludo]::Hola("Juan")
```

## Acceso total a las APIs de .NET desde PowerShell

Esto es posible porque PowerShell tiene acceso completo al runtime de .NET, igual que C#.

```powershell
[Console]::WriteLine("Hola")
[Environment]::GetEnvironmentVariable("PATH")
[IO.File]::ReadAllText("C:\archivo.txt")
```