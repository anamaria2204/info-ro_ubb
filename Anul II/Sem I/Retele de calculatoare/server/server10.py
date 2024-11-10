#Problema 10

# Un client trimite unui server doua siruri de caractere.
# Serverul ii raspunde clientului cu caracterul
# care se regaseste de cele mai multe ori pe
# pozitii identice in cele doua siruri
# si cu numarul de aparitii ale acestui caracter.

def caracter(sir1, sir2):
    char = ""
    max_ap = 0
    nr ={}
    if len(sir1) > len(sir2) :
        lung = len(sir2)
    else:
        lung = len(sir1)
    for i in range(lung):
        if sir1[i] == sir2[i] and sir1[i] != " ":
            c = sir1[i]
            nr[c] = nr.get(c,0) + 1
            if nr[c] > max_ap:
                char = c
                max_ap = nr[c]
    return char, max_ap

import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12316))

server.listen(5)

while True:
    client, addr = server.accept()

    print(f"Conexiune pe {addr}")

    data = client.recv(1024).decode()

    try:
        sir1, sir2 = data.split("|")
    except ValueError:
        client.send("Invalid format")

    c, nr = caracter(sir1, sir2)

    message_sent = f"{c}|{nr}"

    client.send(message_sent.encode())

    client.close()


