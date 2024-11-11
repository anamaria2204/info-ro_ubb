import socket

def pozitii(c, sir):
    sir_rez = []
    for i in range(len(sir)):
        if sir[i] == c:
            sir_rez.append(str(i))
    return " ".join(sir_rez)

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_adrr = ('127.0.0.1',2005)
server.bind(server_adrr)

while True:
    data, client_addr = server.recvfrom(101)
    print(f"Am primit: {data}")
    try:
        c,sir = data.decode().split("|")
        ch = str(c)
        sir_procesare = str(sir)

        sir_rez = pozitii(ch, sir_procesare)
        print(f"Am trimis: {sir_rez}")

        server.sendto(sir_rez.encode(), client_addr)

    except Exception as e:
        server.sendto("Invalid data", client_addr)