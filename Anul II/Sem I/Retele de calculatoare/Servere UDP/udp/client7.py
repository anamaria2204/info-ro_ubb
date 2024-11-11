import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1',2006)

sir = input("Introduceti sirul: ")
i = input("Introduceti pozitia: ")
l = input("Introduceti lungimea: ")

mesaj = f"{sir}|{i}|{l}"
print(f"Am trimis {mesaj}")
client.sendto(mesaj.encode(), server_addr)

raspuns, _ = client.recvfrom(102)
print(f"Subsirul de la pozitia {i} de lungime {l} este: {raspuns.decode()}")

client.close()