import socket

def subsir(sir, i, l):
    sir_rez = []
    lung = 0
    while lung < l:
        lung += 1
        sir_rez.append(sir[i])
        i += 1
    return "".join(sir_rez)

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('localhost', 2006)
server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(102)
    date = data.decode()
    print(f"Am primit de la client: {date}")

    try:
        sir, i, l = date.split("|")
        i_int = int(i)
        l_int = int(l)

        sir_rez = subsir(sir, i_int, l_int)
        print(f"Am trimis: {sir_rez}")
        server.sendto(sir_rez.encode(), client_addr)

    except Exception as e:
        server.sendto("Date invalide", client_addr)