import socket

def prim(numar):
    if numar <= 1:
        return False
    for i in range(2, int(numar)-1):
        if numar % i == 0:
            return False
    return True

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = ('localhost', 2001)
server_socket.bind(server_addr)

while True:
    data, client_address = server_socket.recvfrom(1024)
    print(f"Mesaj primit de la {client_address}: {data.decode()}")

    try:
        # Despachetează datele (se presupune că este un număr)
        numar = int(data.decode())
        ok = prim(numar)

        if ok == 1:
            raspuns = "True"
        else:
            raspuns = "False"
        server_socket.sendto(raspuns.encode(), client_address)
    except ValueError:
        # În caz de eroare (dacă nu se poate converi la număr)
        server_socket.sendto(b"Input invalid", client_address)