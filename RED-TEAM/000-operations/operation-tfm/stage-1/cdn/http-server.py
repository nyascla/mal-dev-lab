# server.py
import http.server
import socketserver

PORT = 8000
DIRECTORY = "./cdn"

class Handler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Servidor escuchando en el puerto {PORT}")
    httpd.serve_forever()
