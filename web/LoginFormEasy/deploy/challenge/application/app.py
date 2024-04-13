from flask import Flask, Blueprint, url_for, render_template, redirect, jsonify, request
from flask_bcrypt import Bcrypt
from pymongo import MongoClient

app = Flask(__name__)
app.config.from_object("application.config.Config")
bcrypt = Bcrypt(app)

client = MongoClient(app.config["MONGO_URI"])
db = client[app.config["DB_NAME"]]
users_collection = db["users"]

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


@app.route("/", methods=["GET","POST"])
def ind():
    return redirect('/login')

@app.route("/login", methods=["GET"])
def index():
    return render_template("login.html")

@app.route("/robots.txt", methods=["GET"])
def robots():
    return render_template("robots.txt")

@app.route("/secret", methods=["GET"])
def secret():
    return render_template("secret.txt")


@app.route("/login", methods=["POST"])
def login():
    content_type = request.headers.get("Content-Type")

    if content_type == "application/json":
        data = request.get_json()
        email = data.get("email")
        password = data.get("password")
    
    else:
        return jsonify({"error": "Unsupported Content-Type"}), 400

    user = users_collection.find_one({"email": email, "password": password})

    if user:
        return render_template("flag.html", flag=open("flag.txt").read())
    else:
        return redirect("/login")
