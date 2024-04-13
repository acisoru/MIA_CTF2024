from flask import Flask, request, render_template, session, url_for, redirect
from my_math import generate_expr, eval_expr

app = Flask(__name__)
app.secret_key = "some_very_secret_key"
app.debug = False

@app.route("/index", methods=["GET", "POST"])
@app.route("/", methods=["GET", "POST"])
def index():
    if not session:
        session["count"] = 0
    if session["count"] == 1000:
        return render_template("index.html", message = "miactf{y0u_4r3_n07_4_r0b07}")
    if not session.get("captcha"):
        session["captcha"] = generate_expr()
        session["answer"] = eval_expr(session["captcha"])
    if request.method == "POST":
        answer = request.form.get("answer")
        try:
            answer = int(answer)
        except:
            session["count"] = 0
            del session["captcha"]
            return render_template("index.html", message = "You entered something bad! <a href='/'>Will you try again?</a>")
        if int(answer) == session["answer"]:
            session["count"] += 1
            session["captcha"] = generate_expr()
            session["answer"] = eval_expr(session["captcha"])
            redirect(url_for("index"))
        else:
            session["count"] = 0
            del session["captcha"]
            return render_template("index.html", message = "You are a robot! <a href='/'>Will you try again?</a>")
    return render_template("index.html", captcha = session["captcha"], count = session["count"])


if __name__=="__main__":
    app.run(debug=True, host='0.0.0.0', port=8080)