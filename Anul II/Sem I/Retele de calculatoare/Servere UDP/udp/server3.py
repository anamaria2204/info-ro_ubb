import socket

def nr_spatii(sir):
    return sir.count(" ")

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('127.0.0.1', 2002)

server.bind(server_addr)

while True:
    data, client_addr = server.recvfrom(100)
    print(f"Mesaj primit de la client: {data}")

    try:
        sir = data.decode()
        nr = nr_spatii(sir)
        raspuns = str(nr)

        print(f"Trimit la client: {raspuns}")
        server.sendto(raspuns.encode(), client_addr)

    except Exception as e:
        server.sendto(b"Input invalid", client_addr)