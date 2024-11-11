import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('localhost', 2009)

hostname = input("Introduceti numele calculatorului: ")
client.sendto(hostname.encode('utf-8'), server_addr)

data, _ = client.recvfrom(1024)
if data == b'\x00\x00\x00\x00':
    print(f"Eroare, {hostname} nu poate fi translatat in adresa ip")
else:
    ip_addr = socket.inet_ntoa(data)
    print(f"Adresa ip este: {ip_addr}")

client.close()