import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('127.0.0.1', 12315))

sir1 = "1 2 3 8 6 5"
sir2 = "3 4 9 2 1"

message = f"{sir1}|{sir2}"

client.send(message.encode())

print(f"Clientul trimite {message}")

dif = client.recv(1024).decode()

print(f"Diferenta multimilor 1 si 2 este: {dif}")

client.close()