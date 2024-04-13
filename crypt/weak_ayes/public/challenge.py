import random
from Crypto.Cipher import AES
from Crypto.Util.number import long_to_bytes
from Crypto.Util.Padding import pad


BLOCK_SIZE = 16


with open('flag.txt', 'rb') as f:
    flag = f.read().strip()


def padding(data: bytes) -> bytes:
    if len(data) < BLOCK_SIZE:
        data += open("/dev/urandom", "rb").read(BLOCK_SIZE-len(data))
    else:
        data = data[:BLOCK_SIZE]
    return data


def keygen():
    step = random.randint(10, 19)
    key = b''
    for i in range(0, 256, step):
        key += long_to_bytes(i)
    return padding(key)


key = keygen()
iv = open("/dev/urandom", "rb").read(BLOCK_SIZE)
cipher = AES.new(key, AES.MODE_CBC, iv)
ct = cipher.encrypt(pad(flag,16))
print(f"iv = {iv.hex()}")
print(f"ct = {ct.hex()}")
