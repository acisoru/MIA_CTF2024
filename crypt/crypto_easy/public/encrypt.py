from Crypto.Util.number import bytes_to_long, long_to_bytes
import random

with open("./flag.txt", "r") as f:
    flag = f.read().strip()
seed = random.randint(1, 1337)
random.seed(seed)
primes = [5, 7, 11, 13, 17, 19, 23]
ciphertext = []
for elem in flag:
    chosen_primes = []
    while len(chosen_primes) != 3:
        i = random.randint(0, len(primes) - 1)
        if primes[i] not in chosen_primes:
            chosen_primes.append(primes[i])
    ciphertext.append([ord(elem) % p for p in chosen_primes])

with open("encrypt.txt", "w") as f:
    f.write(f"{ciphertext = }")
