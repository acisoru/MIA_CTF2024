from flask import Flask, render_template, redirect, jsonify, request
from flask_bcrypt import Bcrypt
import jwt
import random

app = Flask(__name__)
bcrypt = Bcrypt(app)


alphabet = 'abcdefghijklmnopqrstuvwxyz'

with open('/flag.txt','r') as f:
    FLAG = f.read()[:-1]


def get_secret(sec):
    secret = ''
    for i in range(17):
        secret+=sec[i]
    return secret

secret = get_secret(10*random.choice(alphabet) + FLAG)



@app.errorhandler(Exception)
def handle_error(error):
    message = error.description if hasattr(error, "description") else [str(x) for x in error.args]
    
    response = {
        "error": {
            "type": error.__class__.__name__,
            "message": message
            
        }
    }

    return response, error.code if hasattr(error, "code") else 500



@app.route("/", methods=["GET"])
def index():
    return render_template("index.html",context = "")




@app.route('/', methods=["POST"])
def create_token():

    try:
        content_type = request.headers.get("Content-Type")


        if content_type == "application/x-www-form-urlencoded":
            user = request.form.get("user")
            token = request.form.get("token")


        elif content_type == "application/json":
            data = request.get_json()
            user = data.get("user")
            token = data.get("token")

        if user is not None:
            encoded = jwt.encode({'username': user, 'admin': False}, secret, algorithm='HS256')
            message = f'this is your token {encoded}'
            return render_template('index.html',context=message)
        
        if token is  None:
            return render_template('index.html',context='')
    

        decoded = jwt.decode(token, secret, algorithms=['HS256'])
        if "admin" in decoded and decoded["admin"]:
            message = f"hello, admin , this is your secret : {FLAG}"
        elif "username" in decoded:
            message = f"Welcome {decoded['username']}, there are no secrets for you here "
        else:
            message = "There is something wrong with your session, goodbye"
        return render_template('index.html',context = message)
    except Exception as e:
        return render_template('index.html', context = 'try again! smth went wrong ')

