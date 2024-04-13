from pwn import *
import sys
import re
import math

HOST = "localhost"
PORT = 8081

def strategy():
    """Your strategy here!"""
    
    return b"C"
    

conn = remote(HOST, PORT)
# conn.interactive()

data = conn.recvuntil(b"action [C or D] for me: ")
# print(data)

while True:
    if b"New match started!" in data:
        history = []
        enemy_history = []
        
    if b"opponent" in data:
        matches = re.findall(r'You played (\w), opponent played (\w)', data.decode())
        history.append(matches[0][0])
        enemy_history.append(matches[0][1])
        turn = strategy()
        conn.sendline(turn)
    else:
        conn.sendline(b"C")
            
    data = conn.recvuntil(b"action [C or D] for me: ", timeout=2)
    if b"action [C or D] for me:" not in data:
        conn.interactive()
        break
    
    