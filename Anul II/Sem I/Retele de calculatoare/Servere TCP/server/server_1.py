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

def cel_mai_frecvent(sir):
    max = 0
    for i in range(len(sir)):
        if len(pozitii(sir, sir[i])) > max:
            max = len(pozitii(sir, sir[i]))
            char = sir[i]
    return char


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

        sir_nou = cel_mai_frecvent(data)
        sir_nouu = pozitii(data, sir_nou)

        message = f"{sir_nou}|{sir_nouu}"

        print(f"Sending: {message}")

        # Send the result back to the client
        client_socket.send(sir_nou.encode())
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()  # Ensure the client socket is always closed
