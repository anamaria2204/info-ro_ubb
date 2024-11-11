import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2003)

sir = input("Introduceti sirul dorit: ")
print(f"Am trimis la server: {sir}")

client.sendto(sir.encode(), server_addr)

raspuns, _ = client.recvfrom(100)
print(f"Sirul oglindit este: {raspuns.decode()}")

client.close()
