#Probelma 9

# Un client trimite unui server doua siruri de numere.
# Serverul va returna clientului sirul de
# numere care se regaseste in primul sir dar
# NU se regasesc in al doilea.
# (diferenta multimilor 1 si 2)

import socket

def sir(sir1, sir2):
    sir_nou = []

    nr1 = set(map(int, sir1.split()))
    nr2 = set(map(int, sir2.split()))

    sir_nou = nr1.difference(nr2)

    return " ".join(map(str,sorted(sir_nou)))

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('127.0.0.1', 12315))
server.listen(5)

while True:

    client, addr = server.accept()

    print(f"Conectat pe {addr}")

    data = client.recv(1024).decode()

    try:
        sir1, sir2 = data.split("|")
    except ValueError:
        client.send("Invalid format for data")

    sir_nou = sir(sir1, sir2)

    client.send(sir_nou.encode())

    client.close()