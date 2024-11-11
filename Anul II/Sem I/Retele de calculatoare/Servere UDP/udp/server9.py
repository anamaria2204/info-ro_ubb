import socket
import time

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2008)
server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(1024)
    print(f"Cererea primita de la client: {data}")

    curent_time = int(time.time())
    server.sendto(str(curent_time).encode(), client_addr)
    print(f"Timpul curent trimis catre client: {curent_time}")

