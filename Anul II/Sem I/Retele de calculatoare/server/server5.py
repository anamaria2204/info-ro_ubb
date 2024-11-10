#Problema 5

# Un client trimite unui server un numar.
# Serverul va returna clientului sirul divizorilor
# acestui numar.

import socket

def divizori(numar):
    sir = []
    nr = int (numar);
    for i in range(1,nr+1):
        if nr % i == 0:
            sir.append(str(i))
    return " ".join(sir)

server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.bind(('localhost',1239))

server_sock.listen(5)

while True:
    client_sock, addr = server_sock.accept()

    numar = client_sock.recv(1024).decode()

    sir = divizori(numar)

    client_sock.send(sir.encode())
    client_sock.close()
