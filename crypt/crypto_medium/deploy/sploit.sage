import json
from Crypto.Util.number import bytes_to_long, long_to_bytes


def polynomial_gcd(f, g):
    if g == 0:
        return f.monic()
    else:
        return polynomial_gcd(g, f % g)


def FranklinReiter(n, e, c1, c2, a1, b1, a2, b2):
    R.<x> = PolynomialRing(Zmod(n))
    f = (a1 * x + b1) ^ e - c1
    g = (a2 * x + b2) ^ e - c2
    return int(n - polynomial_gcd(f, g).coefficients()[0])


def read_data(file_path):
    with open(file_path, "r") as f:
        return f.readlines()


def main():
    js1, js2 = read_data("./output")
    js1, js2 = json.loads(js1), json.loads(js2)

    data1 = [js1["N"], js1["e"], js1["ct"], js1["a"], js1["b"]]
    data2 = [js2["ct"], js2["a"], js2["b"]]
    n, e, c1, a1, b1 = list(int(x, 16) for x in data1)
    c2, a2, b2 = list(int(x, 16) for x in data2)
    root = FranklinReiter(n, e, c1, c2, a1, b1, a2, b2)
    print(long_to_bytes(root))


if __name__ == "__main__":
    main()
