#!/usr/bin/env python3
import socket

HOST = "127.0.0.1"
PORT = 4444

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"Servidor escuchando en {HOST}:{PORT}")
    conn, addr = s.accept()
    with conn:
        print("Conectado por", addr)
        while True:
            data = conn.recv(4096)
            if not data:
                break
            print("Recibido:", data)
            # responder al cliente (eco)
            conn.sendall(b"echo: " + data)
    
    print("Conexión cerrada")
