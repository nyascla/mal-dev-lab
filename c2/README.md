Cobalt strike

pgp

whatsapp bussines:
    - WhatsApp Cloud API

2) Diagrama de flujo mínimo

WhatsApp (tu móvil) → 2. Librería WhatsApp Web en una máquina (con sesión autenticada por QR) → 3. Tu servidor (webhook/API) recibe el evento message → 4. Procesas (NLP, DB, lógica) → 5. Tu servidor responde a la librería → 6. La librería envía la respuesta a WhatsApp.

3) Requisitos básicos

Entorno servidor: Node.js (recomendado) o Python.

Librería: Baileys o whatsapp-web.js (Node). 
baileys.wiki
+1

Exponer tu servidor local para pruebas: ngrok o localtunnel (permiten recibir webhooks desde la máquina que corre la librería).

Opcional: Docker para aislar la sesión.

Cuenta WhatsApp en un teléfono para escanear QR (sesión multi-dispositivo o clásica).
