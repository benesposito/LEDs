import struct
from serial import Serial
from dataclasses import dataclass, field, astuple
from typing import List

@dataclass
class Color:
	r: int = 0
	g: int = 0
	b: int = 0

@dataclass
class State:
	enabled: bool = False
	mode: int = 0
	brightness: int = 100
	NUM_COLORS: int = 10
	colors: List[Color] = field(default_factory=list)

class SerialCommunicator:
	def __init__(self, device='/dev/ttyUSB0'):
		self.state = State()
		self.arduino = Serial(device)

		for _ in range(self.state.NUM_COLORS):
			self.state.colors.append(Color())

	def send(self):
		packstring = '?iii{}i'.format(3 * self.state.NUM_COLORS)
		payload = struct.pack(packstring, self.state.enabled, self.state.mode, self.state.brightness, self.state.NUM_COLORS, *[val for color in map(astuple, self.state.colors) for val in color])

		print('Sending: {}'.format(self.state))
		self.arduino.write(payload)