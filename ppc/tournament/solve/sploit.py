from pwn import *
import sys
import re
import math

if len(sys.argv) >= 3:
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])
else:
    HOST = "localhost"
    PORT = 8081

def shannon_entropy(s):
    freq = {}
    for c in s:
        if c in freq:
            freq[c] += 1
        else:
            freq[c] = 1
    
    entropy = 0
    total = len(s)
    for count in freq.values():
        probability = count / total
        entropy -= probability * math.log2(probability)
        
    return entropy


def strategy(history, enemy_history, is_enemy_random):
    
    round_number = len(history) + 1
    
    if round_number < 5:
        return [b"C", False]
    
    elif round_number < 15:
        return [enemy_history[-1].encode(), False]
    
    hist_entropy = shannon_entropy("".join(enemy_history[-15:]))
    
    if round_number % 15 == 0:
        print(enemy_history[-15:], shannon_entropy("".join(enemy_history[-15:])))
    
    if hist_entropy > 0.89:
        is_enemy_random = True
    else:
        is_enemy_random = False
    
    if is_enemy_random:
        return [b"D", True]
    else:  
        return [enemy_history[-1].encode(), False]
    

conn = remote(HOST, PORT)
# conn.interactive()

data = conn.recvuntil(b"action [C or D] for me: ")
# print(data)

while True:
    # print(data)
    # print(history[-10:], enemy_history[-10:])
    if b"New match started!" in data:
        history = []
        enemy_history = []
        is_enemy_random = False

    if b"opponent" in data:
        matches = re.findall(r'You played (\w), opponent played (\w)', data.decode())
        history.append(matches[0][0])
        enemy_history.append(matches[0][1])
        turn, is_enemy_random = strategy(history, enemy_history, is_enemy_random)
        conn.sendline(turn)
    else:
        conn.sendline(b"C")
            
    data = conn.recvuntil(b"action [C or D] for me: ", timeout=2)
    if b"action [C or D] for me:" not in data:
        conn.interactive()
        break
    
    
