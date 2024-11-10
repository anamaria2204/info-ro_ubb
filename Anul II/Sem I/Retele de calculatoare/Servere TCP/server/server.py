#Problema 1

# Un client trimite unui server un sir de numere.
# Serverul va returna clientului suma numerelor primite.

import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind(('localhost', 12345))
server_socket.listen(5)

while True:
    client_socket, addr = server_socket.accept()

    print("Client conectat..")

    data = client_socket.recv(1024).decode()

    numbers = map(int, data.split())

    total_sum = sum(numbers)

    client_socket.send(str(total_sum).encode())

    client_socket.close()