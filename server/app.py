from flask import Flask, request
from flask_cors import CORS
import json
from ledscomm import make_comm_device, Color

app = Flask(__name__)
CORS(app)

arduino = make_comm_device("192.168.1.237")


@app.route("/toggle", methods=["POST"])
def toggle():
    data = json.loads(str(request.data, "utf-8"))

    arduino.state.enabled = data["enabled"]

    arduino.send()
    return ("", 204)


@app.route("/submit", methods=["POST"])
def submit():
    data = json.loads(str(request.data, "utf-8"))

    arduino.state.mode = data["mode"]
    arduino.state.brightness = data["brightness"]
    print(data["colors"])

    for i in range(len(data["colors"])):
        arduino.state.colors[i] = Color(*data["colors"][i])

    # param1 = data['param1']
    # param2 = data['param2']

    arduino.send()
    print(arduino.read_ack())
    return ("", 204)


if __name__ == "__main__":
    app.run()
