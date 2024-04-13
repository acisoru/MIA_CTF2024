import socket
import base64
import os
from random import choice
import threading

with open("citations.txt", "r") as f:
    CITATIONS = f.readlines()

ROUNDS = 500

FLAG = os.environ.get("FLAG")

if FLAG is None:
    FLAG = "flag{fake_flag}"


def handle_client(client_socket, client_address):
    client_socket.send(b"Try to beat me!\n\n")
    round_n = 0
    while round_n <= ROUNDS:
        citation = choice(CITATIONS).strip()
        encoded_message = base64.b64encode(citation.encode()).decode()

        client_socket.send(f"Message: {encoded_message}\nAnswer: ".encode())
        client_socket.settimeout(2)
        try:
            response = client_socket.recv(1024)
            if response.decode().strip() == citation:
                round_n += 1
            else:
                client_socket.send(b"Wrong!\n")
                client_socket.close()
                break
        except socket.timeout:
            client_socket.send(b"\n\nTry faster buddy!\n\n")
            client_socket.close()
            break

        if round_n > ROUNDS:
            client_socket.send(f"Good job! Here is your flag: {FLAG}\n".encode())
            break


def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"New connection from {client_address[0]}:{client_address[1]}")

        # Start a new thread to handle the client
        client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
        client_thread.start()

if __name__ == "__main__":
    start_server("0.0.0.0", 8080)
