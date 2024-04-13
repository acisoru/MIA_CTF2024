import socket
import threading
import os
import axelrod as axl 
from tabulate import tabulate
from random import randint
from socket_player import SocketPlayer
from pprint import pprint
from time import sleep


FLAG = os.environ.get("FLAG")

if FLAG is None:
    FLAG = "flag{fake_flag}"
    

def handle_client(client_socket):
    
    client_socket.send(b"Welcome to the tournament!\n")
    client_socket.send(b"Matrix for game is pretty simple.\n\n")
    
    client_socket.send(b" +-----------+\n")
    client_socket.send(b" | - | C | D |\n")     
    client_socket.send(b" +-----------+\n")     
    client_socket.send(b" | C | 3 | 0 |\n")
    client_socket.send(b" +-----------+\n")     
    client_socket.send(b" | D | 5 | 1 |\n")
    client_socket.send(b" +-----------+\n\n")
    
    client_socket.send(b"Win the tournament and get a flag!\nThe tournament begin!\n")
    
    players = [s() for s in axl.axelrod_first_strategies]
    players.append(SocketPlayer(client_socket))
    players.remove(axl.FirstBySteinAndRapoport())
    
    
    tournament = axl.Tournament(players, turns=100, repetitions=1, seed=randint(0, 2**32 - 1))
    
    results = tournament.play()
    
    scores = sorted([sum(i) for i in results.scores],reverse=True)
    
    rows = []
    for i in range(len(results.ranked_names)):
        rows.append([i + 1, "Opponent" if results.ranked_names[i] != "SocketPlayer" else "SocketPlayer", scores[i]])
    
    client_socket.send(b"\nTime for results!\n")
    
    tabulated_results = tabulate(rows, headers=["Position", "Name", "Points"], tablefmt="grid").encode()
    
    client_socket.send(tabulated_results)
    
    if rows[0][1] == "SocketPlayer":
        client_socket.send(f"\nCongratulations! Here is your flag: {FLAG}\n".encode())
    else:
        client_socket.send(f"\nSorry, but first place is not yours! Try next time, bye bye!\n".encode())
    sleep(4)
    client_socket.close()
    
def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"New connection from {client_address[0]}:{client_address[1]}")

        # Start a new thread to handle the client
        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()


if __name__ == "__main__":
    start_server("0.0.0.0", 8081)