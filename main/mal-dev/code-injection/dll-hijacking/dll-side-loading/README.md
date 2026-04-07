el mas habitual

problemas

existencia de bianrio vulnerable a dll hijacking
- no muy rato

permisos de admistrador para escribir dll maliciosas

ioc muy caracteristicos
- dos dlls con el mismo nombre enel mismo proceso
- solo una con firma verificada

cortex: (Low)
![alt text](image.png)

puntos positivos
- no alojar memoria privada RX/RWX
- no cambiar permisos de memoria mapeada
- NO escribir codigo en proceso remoto