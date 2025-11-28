using System;
using System.Runtime.InteropServices;

namespace RedTeam
{
    public class Program
    {
        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern int MessageBoxW(IntPtr hWnd, string text, string caption, uint type);

        [DllImport("user32.dll", CharSet = CharSet.Ansi)]
        public static extern int MessageBoxA(IntPtr hWnd, string text, string caption, uint type);

        public static void Main()
        {
            // MessageBoxA (ANSI) → funciona incluso si el beacon está en proceso WoW64
            MessageBoxA(IntPtr.Zero, "¡Hola desde Sliver execute-assembly!\n\nEste assembly está corriendo 100% en memoria.", 
                       "RedTeam - Sliver Demo 2025", 0x0 | 0x40); // MB_OK | MB_ICONINFORMATION
        }
    }
}