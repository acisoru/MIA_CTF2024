import ast
import random
from sage.all import crt


primes = [5, 7, 11, 13, 17, 19, 23]
with open("./encrypt.txt", "r") as f:
    data = f.read().replace("ciphertext = ", "")

encrypt = ast.literal_eval(data)
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
