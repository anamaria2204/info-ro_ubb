import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12314))

sir1 = "1 2 6 3 4"
sir2 = "2 7 8 4 9 1"

message = f"{sir1}|{sir2}"

client.send(message.encode())

print(f"Trimit la server: {message}")

sir_nou = client.recv(1024).decode()

print(f"Sirul numerelor comune este: {sir_nou}")