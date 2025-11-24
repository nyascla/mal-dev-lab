robocopy "C:\Program Files\Calibre2" "C:\Users\test\Documents\zz" /E /COPY:DAT /R:3 /W:5

# Simular actualizador de software
schtasks /create /tn "CalibreUpdater" /tr "C:\Users\%USERNAME%\AppData\Local\Calibre\calibre-debug.exe -c \"import time; time.sleep(86400)\"" /sc daily /st 09:00