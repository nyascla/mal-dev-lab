# Lab Setup

## Install SHH on Windows
``` bash
Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
Start-Service sshd
Set-Service -Name sshd -StartupType 'Automatic'
```

## Sync
``` bash
function syncwin() {scp -r $PWD test@172.16.41.128:"C:\Users\test\Desktop\test"}
```