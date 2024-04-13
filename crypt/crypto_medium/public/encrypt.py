from Crypto.Util.number import bytes_to_long, long_to_bytes, getStrongPrime, GCD, inverse
import json
import random


def read_flag():
    with open("./flag.txt", "rb") as f:
        return f.read().strip()


def gen_key():
    e = 313
    while True:
        p, q = getStrongPrime(1024), getStrongPrime(1024)
        N = p * q
        phi = (p - 1) * (q - 1)
        if GCD(e, phi) == 1:
            d = inverse(e, phi)
            return N, e, d


def make_padding(data):
    a, b = random.getrandbits(1024), random.getrandbits(1024)
    return a * data + b, a, b


def enc(N, e, pt):
    pt = bytes_to_long(pt)
    pt, a, b = make_padding(pt)
    return pow(pt, e, N), a, b


def dec(N, d, ct, a, b):
    dec = pow(ct, d, N)
    return long_to_bytes((dec - b) // a)


if __name__ == "__main__":
    N, e, d = gen_key()
    flag = read_flag()
    output = "./output"
    with open("output", "w") as f:
        for _ in range(2):
            ct, a, b = enc(N, e, flag)
            data = json.dumps({"N": f"{N:x}", "e": f"{e:x}", "ct": f"{ct:x}", "a": f"{a:x}", "b": f"{b:x}"})
            pt = dec(N, d, ct, a, b)
            assert pt == flag
            f.write(data + "\n")
