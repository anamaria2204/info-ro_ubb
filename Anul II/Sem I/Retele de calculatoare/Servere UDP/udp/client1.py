import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_addr = ('127.0.0.1', 2000)

nr1 = input("Introduceti primul numar: ")
nr2 = input("Introduceti al doilea numar: ")

mesaj = f"{nr1}|{nr2}"
client_socket.sendto(mesaj.encode(), server_addr)

raspuns, _ = client_socket.recvfrom(1024)
print(f"{raspuns.decode()}")

client_socket.close()