from flask import Flask, request
from flask_cors import CORS
import os
import json

mode = 0
brightness = 50
colors = []

app = Flask(__name__)
CORS(app)

@app.route('/submit', methods=['POST'])
def submit():
	data = json.loads(str(request.data, 'utf-8'))

	mode = data['mode']
	colors = data['colors']

	colors_str = ''

	for c in colors:
		colors_str += str(c[0]) + ',' + str(c[1]) + ',' + str(c[2]) + ','

	print('echo "{};{};{};{};" > /dev/ttyUSB0'.format(mode, brightness, len(colors), colors_str))
	return ('', 204)

if __name__ == '__main__':
    app.run()
