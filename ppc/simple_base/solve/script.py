from pwn import *
import base64
import sys


if len(sys.argv) < 3:
    conn = remote("localhost", 12345)
else:
    conn = remote(sys.argv[1], sys.argv[2])

round = 0

while round <= 500:
    conn.recvuntil(b"Message: ")
    base64_string = conn.recvuntil(b"\n").strip()
    conn.recvuntil(b"Answer: ")

    decoded_data = base64.b64decode(base64_string)

    conn.sendline(decoded_data)

    round += 1

print(conn.recvuntil(b"\n"))

conn.close()
