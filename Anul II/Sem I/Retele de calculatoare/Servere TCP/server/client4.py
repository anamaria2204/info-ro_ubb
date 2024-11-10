import socket

# Crearea socketului client
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectarea la serverul de pe localhost, portul 5678
client_socket.connect(('localhost', 5678))

# Șirurile ordonate care trebuie trimise la server
sir1 = "aabbccdd"
sir2 = "abcdeefg"

# Trimiterea șirului 1
client_socket.sendall(sir1.encode())  # Folosim sendall pentru a ne asigura că tot mesajul este trimis
print(f"Sirul 1 trimis: {sir1}")

# Trimiterea șirului 2
client_socket.sendall(sir2.encode())  # Folosim sendall pentru a trimite complet mesajul
print(f"Sirul 2 trimis: {sir2}")

# Primirea și afișarea șirului interclasat de la server
sir_nou = client_socket.recv(1024).decode()
print(f"Sirul nou obținut este: {sir_nou}")

# Închidem conexiunea cu serverul
client_socket.close()
