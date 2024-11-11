import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2004)

nr = input("Introduceti numarul dorit: ")
nr_int = int(nr)

while nr_int < 0 or nr_int > 255:
    print("Introduceti un numar corect!")
    nr = input("Introduceti numarul dorit: ")

print(f"Trimit la server: {nr}")
client.sendto(nr.encode(), server_addr)

raspuns, _ = client.recvfrom(255)
rez = str(raspuns.decode())
print(f"Sirul de divizori este: {rez}")

client.close()