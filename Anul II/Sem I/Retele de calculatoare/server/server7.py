# Problema 7

# Un client trimite unui server un sir de caractere
# si doua numere (fie acestea s, i, l).
# Serverul va returna clientului subsirul de lungime l
# a lui s care incepe la pozitia i.

import socket

def subsir(sir, i, l):
    sir_nou =[]
    lg = 1
    iint = int(i)
    lint = int(l)
    lungime = len(sir)
    j = 0
    while j < lungime :
        if j == iint :
            while lg <= lint :
                sir_nou.append(sir[j])
                lg += 1
                j += 1
        j += 1
    return "".join(sir_nou)


serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv_sock.bind(('localhost', 12312))
serv_sock.listen(5)

while True:
    client_sock, addr = serv_sock.accept()
    print(f"Connect to {addr}")

    data = client_sock.recv(1024).decode()
    try:
        sir, i, l = data.split("|")
        print(f"Sirul este: {sir}")
        print(f"Pozitia este: {i}")
        print(f"Lungimea este: {l}")
    except ValueError:
        client_sock.send("Invalid format for data")
        continue

    sub_sir = subsir(sir, i, l)

    client_sock.send(sub_sir.encode())

    print(f"Subsirul trimis este: {sub_sir}")

    client_sock.close()



