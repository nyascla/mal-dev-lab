using System;
using System.IO;

class Program
{
    static void Main()
    {
        // Ruta al escritorio del usuario actual
        string desktop = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);

        // Ruta del archivo a crear
        string filePath = Path.Combine(desktop, "prueba_desde_dotnet.txt");

        // Contenido
        string contenido = "Archivo creado correctamente desde una app .NET";

        // Crear el archivo
        File.WriteAllText(filePath, contenido);

        Console.WriteLine($"Archivo creado en: {filePath}");
    }
}
