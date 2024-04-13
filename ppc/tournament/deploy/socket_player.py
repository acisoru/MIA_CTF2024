from axelrod.action import Action
from axelrod.player import Player
import socket

class SocketPlayer(Player):
    """
        Rewritten "Human" class that allows to play tournament from socket.
    """

    name = "SocketPlayer"

    def __init__(self, client_socket) -> None:
        super().__init__()
        self.client_socket = client_socket
        
        self.symbols = {
            Action.C: "C",
            Action.D: "D"
        }
    def __repr__(self):
        return "SocketPlayer"

    def strategy(self, opponent: Player):
        
        curr_turn_id = len(self.history) + 1
        
        if curr_turn_id == 1:
            self.client_socket.send(f"New match started! Turn {curr_turn_id} action [C or D] for me: ".encode())
            
            action = self.client_socket.recv(4).decode().strip()
            
            if action == "C" or action == "D":
                return Action.from_char(action)
            else: 
                self.client_socket.send(b"Invalid action! Tournament aborted!\n")
                raise ValueError("Invalid action!")
        
        self.client_socket.send("Turn {}: You played {}, opponent played {}\n".format(
            curr_turn_id - 1,
            self.symbols[self.history[-1]],
            self.symbols[self.history.coplays[-1]]
            ).encode())
        
        self.client_socket.send(f"Turn {curr_turn_id} action [C or D] for me: ".encode())
        
        if curr_turn_id == 40:
            self.client_socket.settimeout(2)
        try:
            action = self.client_socket.recv(4).decode().strip()
        except socket.timeout:
                    self.client_socket.send(b"\n\nTry faster buddy!\n\n")
                    self.client_socket.close()
                    exit(0)
            
        if action == "C" or action == "D":
                return Action.from_char(action)
        else:
                self.client_socket.send(b"Invalid action! Tournament aborted!\n")
