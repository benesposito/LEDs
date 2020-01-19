from flask import Flask, request
import os

mode = 0
brightness = 50
colors = []

app = Flask(__name__)

@app.route('/set', methods=['POST'])
def setColor():
	data = json.loads(str(request.data, 'utf-8'))
	print(data)
	return ('', 204)

@app.route('/submit')
def submit():
	colors_str = ''

	for c in colors:
		colors_str += c[0] + ',' + c[1] + ',' + c[2] + ','

	os.system('echo "{};{};{};{},{},{},;" > /dev/ttyUSB0'.format(mode, brightess, len(colors), colors_str))
	return ('', 204)

if __name__ == '__main__':
    app.run()
