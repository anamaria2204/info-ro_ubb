import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('127.0.0.1', 12316))

sir1 = "ana are mare"
sir2 = "are ana mar"

message = f"{sir1}|{sir2}"

print(f"Clientul trimite: {message}")

client.send(message.encode())

raspuns = client.recv(1024).decode()

try:
    char, nr = raspuns.split("|")
except ValueError:
    client.send("Raspuns invalid")

print(f"Caracterul cel mai frecvent este: {char}")
print(f"Nr de aparitii {nr}")