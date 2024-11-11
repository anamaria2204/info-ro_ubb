import socket

def cmmdc(a, b):
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

def cmmmc(a, b):
    return a*b// cmmdc(a,b)


server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2007)
server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(256)

    print(f"Am primit: {data.decode()}")
    numere = data.decode().split("|")
    nr1 = int(numere[0])
    nr2 = int(numere[1])

    c1 = cmmdc(nr1, nr2)
    c2 = cmmmc(nr1, nr2)

    raspuns = f"{c1}|{c2}"

    print(f"Am trimis: {raspuns}")
    server.sendto(raspuns.encode(), client_addr)
