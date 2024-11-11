import socket

def oglindit(sir):
    return sir[::-1]

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2003)

server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(100)
    print(f"Am primit de la client: {data}")

    try:
        sir = data.decode()
        sir_rezultat = oglindit(sir)

        print(f"Trimit la client: {sir_rezultat}")
        server.sendto(sir_rezultat.encode(), client_addr)

    except Exception as e:
        server.sendto("Invalid data", client_addr)