import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2005)

c = input("Introduceti caracterul dorit: ")
sir = input("Introduceti sirul dorit: ")

mesaj = f"{c}|{sir}"

print(f"Am trimis: {mesaj}")
client.sendto(mesaj.encode(), server_addr)

raspuns, _ = client.recvfrom(101)
print(f"Pozitiile caracterului {c} in sirul '{sir}' sunt: {raspuns.decode()}")

client.close()