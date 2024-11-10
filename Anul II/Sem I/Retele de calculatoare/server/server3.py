#Problema 3cd rete

# Un client trimite unui server un sir de caractere.
# Serverul va returna clientului acest sir oglindit
# (caracterele sirului in ordine inversa).

import socket

def oglindit(sir):
    return sir[::-1]

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12347))
server_socket.listen(5)

while True:

    client_socket, addr = server_socket.accept()

    data = client_socket.recv(1024).decode()

    sir_invers = oglindit(data)

    client_socket.send(str(sir_invers).encode())

    client_socket.close()