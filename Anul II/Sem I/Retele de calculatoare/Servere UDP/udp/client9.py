import socket
import time

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2008)

try:
    client.sendto(b'', server_addr)
    data, _ = client.recvfrom(1024)

    print("Data si ora primita de la server: ",
          time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(int(data.decode()))))

finally:
    client.close()