import socket

client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_sock.connect(('localhost', 12312))

sir = "ana are mere"
i = 4
l = 3

message = f"{sir}|{i}|{l}"

client_sock.send(message.encode())

print(f"Clientul trimite sirul de intrare: {message}")

sir_nou = client_sock.recv(1024).decode()

print(f"Subsirul cerut este: {sir_nou}")