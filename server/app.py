from flask import Flask, request
from flask_cors import CORS
import json
from ledscomm import SerialCommunicator

app = Flask(__name__)
CORS(app)

arduino = SerialCommunicator('/dev/ttyUSB1')

@app.route('/toggle', methods=['POST'])
def toggle():
	print('here')
	data = json.loads(str(request.data, 'utf-8'))
	arduino.state.enabled = data['enabled']
	arduino.send()
	return ('', 204)

@app.route('/submit', methods=['POST'])
def submit():
	data = json.loads(str(request.data, 'utf-8'))

	arduino.state.mode = data['mode']
	arduino.state.brightness = data['brightness']
	for color in data['colors']:
		print(color)

	#param1 = data['param1']
	#param2 = data['param2']

	arduino.send()

	return ('', 204)

if __name__ == '__main__':
    app.run()
