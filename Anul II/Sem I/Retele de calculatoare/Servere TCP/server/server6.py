# Problema 6

# Un client trimite unui server un sir de caractere si un caracter.
# Serverul va returna clientului toate pozitiile
# pe care caracterul primit se regaseste in sir.

import socket

def pozitii(sir, c):
    sir_poz = []

    # Loop through the string by index
    for i in range(len(sir)):
        if sir[i] == c:
            sir_poz.append(str(i))

    return " ".join(sir_poz) if sir_poz else "Character not found"

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 12311))
server_socket.listen(5)

print("Server is listening on port 12311...")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Connected to {addr}")

    try:
        # Set a timeout for the socket to avoid blocking
        client_socket.settimeout(10)

        # Receive the combined message from the client
        data = client_socket.recv(1024).decode()
        print(f"Received data: {data}")

        # Split the data using the separator
        try:
            sir, c = data.split("|")
        except ValueError:
            client_socket.send("Error: Invalid data format.".encode())
            continue

        # Ensure that only a single character is received
        if len(c) != 1:
            sir_nou = "Error: Please send a single character."
        else:
            # Find positions of the character in the string
            sir_nou = pozitii(sir, c)

        print(f"Sending: {sir_nou}")

        # Send the result back to the client
        client_socket.send(sir_nou.encode())
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()  # Ensure the client socket is always closed
