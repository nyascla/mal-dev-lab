using System;
using System.Runtime.InteropServices;

namespace RedTeam
{
    public class Entry
    {
        [DllImport("user32.dll", CharSet = CharSet.Ansi)]
        static extern int MessageBoxA(IntPtr h, string t, string c, uint type);

        [STAThread]
        public static void Execute()
        {
            MessageBoxA(IntPtr.Zero, "Sliver + .NET = amor verdadero", "RedTeam 2025", 0x40);
        }
    }
}