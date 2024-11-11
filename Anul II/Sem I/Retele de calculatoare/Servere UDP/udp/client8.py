import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2007)

nr1 = int(input("Introduceti primul numar: "))
nr2 = int(input("Introduceti al doilea numar: "))

while (nr1 < 0 or nr2 < 0) or (nr1 > 255 or nr2 > 255):
    print("Datele nu sunt valide!")
    nr1 = input("Introduceti primul numar: ")
    nr2 = input("Introduceti al doilea numar: ")

mesaj = f"{str(nr1)}|{str(nr2)}"
print(f"Trimit: {mesaj}")

client.sendto(mesaj.encode(), server_addr)

raspuns, _ = client.recvfrom(256)
try:
    c1, c2 = raspuns.decode().split("|")
    print(f"Am primit cmmdc: {c1} si cmmmc {c2}")
except Exception as e:
    print("Nu am primit datele corespunzatoare")