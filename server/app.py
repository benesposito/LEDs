from flask import Flask, request
from flask_cors import CORS
import os
import json

mode = 0
brightness = 50
colors = []

app = Flask(__name__)
CORS(app)

def execute_and_log(command):
	print(command)
	os.system(command) # TODO: use alternative to os.system

@app.route('/toggle', methods=['POST'])
def toggle():
	data = json.loads(str(request.data, 'utf-8'))
	enabled = 1 if data['enabled'] else 0

	execute_and_log(f'echo "{enabled};" > /dev/ttyUSB0')

	return ('', 204)

@app.route('/submit', methods=['POST'])
def submit():
	data = json.loads(str(request.data, 'utf-8'))

	mode = data['mode']
	colors = data['colors']
	colors_len = len(colors)
	brightness = data['brightness']
	param1 = data['param1']
	param2 = data['param2']

	if mode == 1: # Solid
		color = colors[param1]
		colors_str = '{},{},{},'.format(color[0], color[1], color[2])
		colors_len = 1
	else:
		colors_str = ''
		for c in colors:
			colors_str += str(c[0]) + ',' + str(c[1]) + ',' + str(c[2]) + ','

	execute_and_log(f'echo "{mode};{brightness};{colors_len};{colors_str};" > /dev/ttyUSB0')

	return ('', 204)

if __name__ == '__main__':
    app.run()
