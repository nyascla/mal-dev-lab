using System;
using System.Reflection;

class Program
{
    static void Main()
    {
        var dll = Assembly.LoadFrom("MiniDll.dll");

        var type = dll.GetType("MiniDll.Actions");
        var method = type.GetMethod("Run");

        method.Invoke(null, null);
    }
}
