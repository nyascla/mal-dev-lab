# CALIBRE: Side Loading

Ejemplo calibre

Mirando un poco por hijacklibs veemos que calibre es vulnerable a side loading

https://hijacklibs.net/entries/3rd_party/calibre/calibre-launcher.html

Descargamos la version portable de calibre y la ponermos en una carpeta creible pero donde un usuario no privilegiado pueda escribir

https://calibre-ebook.com/es/download_portable

Nuestro target sera: calibre-launcher.dll

Vamos a utilizar la tecnica de dll-proxy

creamos el proxy.def

compilamos la dll maliciosa

ahora ya en el sistema victima

renombeamos la dll antigua

copiamos la nueva y ejecutamos calibre sin interfaz grafica por ejemplo con 

calibre-debug.exe -g

y ya esta