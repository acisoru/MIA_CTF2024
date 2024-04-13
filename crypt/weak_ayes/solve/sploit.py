#!/usr/bin/python3
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Util.number import long_to_bytes
import sys

ct = sys.argv[2]
ct = long_to_bytes(int(ct,16))
BS = 16
iv = sys.argv[1]
iv = long_to_bytes(int(iv,16))

key_set =  []
key_for_decode = []
key2  = []
key1 = []

for i in range(10,20):
    key = b''
    for j in range(0,256,i):
        key += long_to_bytes(j)
    key_set.append(key)
 
        

for i in range(256):
    key1.append(long_to_bytes(i))
    for j in range(256):
        key2.append(long_to_bytes(i)+long_to_bytes(j))

for key in key_set:
    if BS - len(key) == 2:
        for random_letters in key2:
            key_for_decode.append(key+random_letters)
    elif BS - len(key) == 1:
        for random_letter in key1:
            key_for_decode.append(key+random_letter)
    else:
        key_for_decode.append(key[:16])



for key in key_for_decode:
    cipher = AES.new(key, AES.MODE_CBC, iv)

    pt = cipher.decrypt(ct)

    if b'miactf' in pt:
        print(pt)
        

