#Problema 4

# Un client trimite unui server doua siruri de caractere ordonate.
# Serverul va interclasa cele doua siruri si
# va returna clientului sirul rezultat interclasat.

import socket

def interclasare(sir1, sir2):
    sir3 = []
    i, j = 0, 0
    while i < len(sir1) and j < len(sir2):
        if sir1[i] <= sir2[j]:
            sir3.append(sir1[i])
            i += 1
        else:
            sir3.append(sir2[j])
            j += 1
    sir3.extend(sir1[i:])
    sir3.extend(sir2[j:])
    return "".join(sir3)

socket_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_server.bind(('localhost', 5678))  # Schimbă portul
socket_server.listen(5)

print("Serverul ascultă pe portul 5678...")

while True:
    socket_client, addr = socket_server.accept()
    print(f"Conectat cu: {addr}")

    sir1 = socket_client.recv(1024).decode()

    print(f"sirul 1: {sir1}")

    sir2 = socket_client.recv(1024).decode()

    print(f"Sirul 2: {sir2}")

    sir_nou = interclasare(sir1, sir2)

    print(f"Sirul nou este: {sir_nou}")

    socket_client.send(sir_nou.encode())
    socket_client.close()
