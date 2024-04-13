import ast
from Crypto.Util.number import long_to_bytes, inverse

p = 4994284531899054937496242914822682451274452982107661887143
Q = (2877061784601320321131456864086665758834694992527216096098, 4611871791775821137478386312974856029672572278672379567408)
G = (599360643237435644454457448648348834185789563949652537104, 2661351407143699579618541073980236209346100936670370784209)

def pohlig_hellman(G, Q):
    order = G.order()
    divs = list(factor(order))
    print(divs)
    factors = [elem[0] ^ elem[1] for elem in divs]
    dlogs = []
    for fac in factors:
        print(f"working with factor {fac}")
        _G = G * (order // fac)
        _Q = Q * (order // fac)
        dlogs.append(discrete_log(_Q, _G, operation="+"))
    return crt(dlogs, factors)

gx, gy = G
qx, qy = Q

a = ((gy ** 2 - gx ** 3 - qy ** 2 + qx ** 3) * inverse(gx-qx, p)) % p
b = (gy ** 2 - gx ** 3 - a * gx) % p
assert (gx ** 3 + a * gx + b) % p == gy ** 2 % p
assert (qx ** 3 + a * qx + b) % p == qy ** 2 % p

E = EllipticCurve(GF(p), [a, b])
G = E(gx, gy)
Q = E(qx, qy)

print(hex(int(a)))
print(hex(int(b)))
print(factor(E.order()))
print(long_to_bytes(int(pohlig_hellman(G, Q))))
