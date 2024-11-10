import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12346))

sir = input("Sirul dorit este: ")

#sir = "ceva mai tare nu este"

print(f"Clientul trimite sirul: {sir}")

client_socket.send(sir.encode())

numar = client_socket.recv(1024).decode()

print(f"Numarul de spatii este: {numar}")

client_socket.close()