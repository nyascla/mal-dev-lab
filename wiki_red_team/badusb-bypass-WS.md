https://www.youtube.com/watch?v=1YmLwPF2lUc

## AMSI bypass (AV Evasion)

Antimalware Scan Interface - middlem main entre script y WD

amsi.dll - amsiscanbuffer() - modificaremos la funcion para que siempre devuelva lo mismo

desde un script combinando poweshell y c# utilizaremos getprocaddress loadlibrary y virutalprotect prara cargar amsi.dll en memoria

con la marshall copy tecnic modificareemos el dea eax para que siempre devuelva lo mismo

https://learn.microsoft.com/es-es/windows/win32/api/amsi/nf-amsi-amsiscanbuffer

si la funcion devuelve un hresult cualquier script se puede ejecutar

https://learn.microsoft.com/es-es/shows/inside/hresult

invoque ofuscation for powershell

la parte de c# puede dar problemas a la hora de ofuscar, cuidao ahi

## Execution policy bypass

Ejecutar scripts no esta permitido en un equipo para usuaios no administradores

podemos cambair la politica para nuestro usuaio

set-executionpolicy unrestricted --scope currentuser

## Payload Runner Development

lookupfunc -  busca asm referencias en memoria
getdelegatetype - set argumente types

virtualalloc

otra vez con la tecnica de marshall copy pasamos el paylaod a memoria

depues lo ejecutamos con create thred function

## Deploying Attack 

programar el fliper

## Post-exploit persistance

podemos hacer movimiento lateral hacia otros procesos