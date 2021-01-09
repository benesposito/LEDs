from ledscomm import USBDevice, UDPDevice, Arduino, Color, State
import dataclasses
import sys
from typing import Callable, Any

def query_for_variable(name: str, default_value: Any , validation_expression: Callable[[int], bool]=lambda x: True) -> int:
	while True:
		label = '{:s}[{}]: '.format(name, default_value)
		input_value: str = input(label)
		
		if not input_value:
			return default_value

		if not input_value.lstrip('-').isnumeric():
			continue

		value = int(input_value)
		
		if validation_expression(value):
			return type(default_value)(value)
			
		

# usb_device = USBDevice('/dev/ttyS7')

# arduino = Arduino(usb_device)
# arduino.state.enabled = False
# ret = arduino.send()
# print(ret)

# count = 0
# while True:
# 	if usb_device.io.in_waiting > 0:
# 		# print(usb_device.io.read().decode('utf-8'), end='')
		
# 		if count % 50 == 0:
# 			arduino.send()
# 			print('sent')
# 			count = 0

# 		count += 1

arduino = Arduino('10.185.250.20')

state = State(
	enabled=True,
	mode=1,
	brightness=100
)

default_color = Color(0, 0, 0)

if True:
	state.enabled = query_for_variable('enabled', True, lambda x: x == 0 or x == 1)
	state.mode = query_for_variable('mode', 1, lambda x: x >= 0)
	state.brightness = query_for_variable('brightness', 100, lambda x: 0 <= x < 256)
	num_colors = query_for_variable('number of colors', 1, lambda x: 0 < x <= 10)

	for i in range(num_colors):
		state.colors[i].r = query_for_variable('color_%d.r' % (i), default_color.r, lambda x: 0 <= x < 256)
		state.colors[i].g = query_for_variable('color_%d.g' % (i), default_color.g, lambda x: 0 <= x < 256)
		state.colors[i].b = query_for_variable('color_%d.b' % (i), default_color.b, lambda x: 0 <= x < 256)

	print()

print(state)

arduino.state = state
# arduino.send()


# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock.connect(('10.185.250.20', 1111))
# sock.send(b'test\n')
# print('connected')
