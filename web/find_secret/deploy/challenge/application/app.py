from flask import Flask, render_template, redirect, jsonify, request
from flask_bcrypt import Bcrypt


app = Flask(__name__)
bcrypt = Bcrypt(app)


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
    return render_template("index.html")



@app.route('/super/secret/information', methods=["GET"])
def secret():
    return render_template('secret.html')
