import requests
from my_math import eval_expr

curl = requests.session()
i = 0
req = curl.get("http://127.0.0.1:8080")
expr = req.text.split('<div style="text-align: center;">\n')[1].split("\n")[0].strip()
while i != 1000:
    req = curl.post("http://127.0.0.1:8080", data={"answer": eval_expr(expr)})
    expr = req.text.split('<div style="text-align: center;">\n')[1].split("\n")[0].strip()
    i += 1
req = curl.post("http://127.0.0.1:8080", data={"answer": eval_expr(expr)})
print(req.text)