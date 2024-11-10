import socket

client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_sock.connect(('localhost', 1239))

numar = 10

print(f"clientul trimite: {numar}")

client_sock.send(str(numar).encode())

sir = client_sock.recv(1024).decode()

print(f"Clintul a primit sirul de divizori: {sir}")