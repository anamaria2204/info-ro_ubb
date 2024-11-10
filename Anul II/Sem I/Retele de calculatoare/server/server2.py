#Problema 2

# Un client trimite unui server un sir de caractere.
# Serverul va returna clientului
# numarul de caractere spatiu din sir.
import socket

def numar_spatii(String) :
    return String.count(" ")


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind(('localhost', 12346))
server_socket.listen(5)

while True:
    client_socket, addr = server_socket.accept()

    data = client_socket.recv(1024).decode()

    number = numar_spatii(data)

    client_socket.send(str(number).encode())

    client_socket.close()

