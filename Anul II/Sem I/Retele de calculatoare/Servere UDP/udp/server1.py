import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('127.0.0.1', 2000)
server_socket.bind(server_address)

while True:

    data, client_addr = server_socket.recvfrom(1024)
    print(f"Mesaj primit de la {client_addr}: {data.decode()}")

    try:
        numere = data.decode().split("|")
        nr1 = int(numere[0])
        nr2 = int(numere[1])

        suma = nr1 + nr2

        raspuns = f"Suma este: {suma}"

        server_socket.sendto(raspuns.encode(), client_addr)

    except Exception as e:
        print(f"Eroare la procesarea datelor: {e}")
        server_socket.sendto(b"Date invalide!", client_addr)