import socket

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server on localhost and port 12311
client_socket.connect(('localhost', 12311))
sir = "ana are meree"

# Send the combined message to the server
client_socket.sendall(sir.encode())
print(f"Clientul trimite: {sir}")

# Receive the positions from the server
sir_nou = client_socket.recv(1024).decode()
#char, pozitii = sir_nou.split("|")
print(f"Mesaj: {sir_nou}")
client_socket.close()  # Close the connection
