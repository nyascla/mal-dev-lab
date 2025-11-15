# server.py
import http.server
import socketserver

PORT = 8000
DIRECTORY = "C:\\Users\\test\\Desktop\\mal-dev-lab\\c2\\files"  # Carpeta con el binario que quieres servir

class Handler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Servidor escuchando en el puerto {PORT}")
    httpd.serve_forever()
