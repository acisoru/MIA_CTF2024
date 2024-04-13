import ast
import random
from sage.all import crt


primes = [5, 7, 11, 13, 17, 19, 23]
encrypt = ciphertext = [[10, 4, 14], [3, 13, 0], [6, 5, 2], [4, 14, 1], [1, 12, 2], [3, 11, 0], [9, 2, 8], [7, 5, 4], [4, 10, 4], [9, 16, 4], [10, 9, 14], [16, 3, 4], [5, 7, 2], [0, 7, 10], [4, 2, 1], [5, 5, 14], [15, 7, 16], [0, 4, 10], [3, 7, 6], [9, 6, 10], [4, 7, 4], [7, 14, 4], [15, 3, 7], [7, 0, 8], [9, 5, 6], [11, 8, 4]]

for i in range(1, 1338):
    flag = ""
    random.seed(i)
    for elem in encrypt:
        chosen_primes = []
        while len(chosen_primes) != 3:
            i = random.randint(0, len(primes) - 1)
            if primes[i] not in chosen_primes:
                chosen_primes.append(primes[i])
        x = int(crt(elem, chosen_primes))
        flag += chr(x)
    if flag.startswith("miactf{"):
        print(flag)
        break
