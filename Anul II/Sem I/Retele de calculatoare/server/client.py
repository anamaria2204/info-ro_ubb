import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 12345))

numbers = input("Enter the numbers: ")
#numbers = "10 20 30"

print(f"Clientul trimite: {numbers}")
client_socket.send(numbers.encode())

data = client_socket.recv(1024).decode()

print(f"Clientul primeste suma: {data}")

client_socket.close()