import socket
import struct

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('localhost', 2009)
server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(1024)
    hostname = data.decode('utf-8').strip()
    print(f"Hostnamr primit: {hostname}")

    try:
        ip_addr = socket.gethostbyname(hostname)
        print(f"Adresa IP pentru {hostname} este {ip_addr}")

        #convertirea adresei ip din format text in 4 octeti
        packed_ip = socket.inet_aton(ip_addr)

        server.sendto(packed_ip, client_addr)
    except socket.gaierror:
        server.sendto(b'\x00\x00\x00\x00', client_addr)
        print(f"Eroare: Numele {hostname} nu poate fi traslatat in adresa ip")