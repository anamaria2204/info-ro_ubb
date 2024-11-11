import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 2001)


numar = input("Introduceți un număr: ")

client_socket.sendto(numar.encode(), server_address)
raspuns, _ = client_socket.recvfrom(1024)
print(f"Răspuns de la server: {raspuns.decode()}")

client_socket.close()