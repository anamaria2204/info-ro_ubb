import socket

def divizori(nr):
    sir = []
    for i in range(1, nr+1):
        if nr % i == 0:
            sir.append(str(i))
    return " ".join(sir)

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2004)

server.bind(server_addr)

while True:

    data, client_addr = server.recvfrom(1024)

    print(f"Am primit: {data.decode()}")
    nr = data.decode()
    nr_int = int(nr)

    sir_rez = divizori(nr_int)
    print(f"Am trimis: {sir_rez}")

    server.sendto(sir_rez.encode(), client_addr)
