import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12347))

sir = "ana are mere"

print(f"Clientul trimite sirul: {sir}")

client_socket.send(sir.encode())

sir_invers = client_socket.recv(1024).decode()

print(f"Clientul primeste sirul inversat: {sir_invers}")

client_socket.close()