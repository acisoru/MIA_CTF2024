from application.app import app




if __name__ == "__main__":
    app.run(host="0.0.0.0", port=4444, threaded=True, debug=False)