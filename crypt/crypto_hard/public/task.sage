from Crypto.Util.number import bytes_to_long
import json
with open("./flag.txt", "rb") as f:
    FLAG = f.read().strip()

with open("./curve.json") as f:
    curve_params = json.loads(f.read())


def public_key():
	d = bytes_to_long(FLAG)
	return G * d

#curve parameters
p = int(curve_params["field"]["p"], 16)
a = int(curve_params["a"], 16)
b = int(curve_params["b"], 16)
E = EllipticCurve(GF(p), [a, b])

G = E.gens()[0]
Q = public_key()
print(p)
print(Q.xy())
print(G.xy())
