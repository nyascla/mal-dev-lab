# Ruta hardcodeada al ejecutable
$ProgramPath = "C:\Users\test\Desktop\mal-dev-lab\red-team-utils\delivery\flipper-zero\bad-usb\messagebox.exe"

# Nombre de la entrada en el registro
$Name = "MiPrograma"

# Validar que el archivo existe
if (-Not (Test-Path $ProgramPath)) {
    Write-Host "Error: El archivo no existe en la ruta especificada."
    exit
}

# Ruta en el registro
$regPath = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"

# Añadir al registro
Set-ItemProperty -Path $regPath -Name $Name -Value "`"$ProgramPath`""