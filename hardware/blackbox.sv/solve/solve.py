import string

ciphertext = [287, 283, 259, 265, 276, 266, 305, 280, 259, 278, 260, 285, 259, 278, 263, 245, 280, 259, 265, 289, 83,
              290, 269, 245, 83, 281, 245, 259, 285, 263, 281, 80, 287, 89, 303]
f = lambda x: (x & 3) + (x & 0xFD) + (x & 0xFE) + (x & 99) + (x & 11) - (x & 55)
M = {}
for i in (string.ascii_letters + string.digits + '_{}'):
    M[f(ord(i))] = i

plaintext = ''
for c in ciphertext:
    plaintext += M[c]

print(plaintext)  # miactf{hardware_hack1ng_1s_awes0m3}
