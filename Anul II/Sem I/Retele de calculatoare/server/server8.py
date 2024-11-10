# Problema 8

# Un client trimite unui server doua siruri de numere.
# Serverul va returna clientului sirul de numere
# comune celor doua siruri primite.

import socket

def comune(sir1, sir2):
    sir =[]
    nr1 = set(map(int, sir1.split()))
    nr2 = set(map(int, sir2.split()))

    sir = nr1.intersection(nr2)

    return " ".join(map(str, sir))

serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv.bind(('localhost', 12314))
serv.listen(5)

while True:

    client, addr = serv.accept()

    print(f"conexiune pe {addr}")

    data = client.recv(1024).decode()

    try:
        sir1, sir2 = data.split("|")
    except ValueError:
        client.send("Invalid format for data")

    sir = comune(sir1, sir2)

    client.send(sir.encode())

    client.close()