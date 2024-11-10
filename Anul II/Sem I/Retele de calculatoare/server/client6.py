import socket

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server on localhost and port 12311
client_socket.connect(('localhost', 12311))

try:
    # Data to send
    sir = "ana are mere"

    # Send the combined message to the server
    client_socket.sendall(sir.encode())
    print(f"Clientul trimite: {sir}")

    # Receive the positions from the server
    sir_nou = client_socket.recv(1024).decode()
    print(f"Pozitiile: {sir_nou}")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    client_socket.close()  # Close the connection
