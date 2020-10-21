from enum import Enum
from dataclasses import dataclass, field, astuple
from typing import List
import struct
from serial import Serial
import socket

@dataclass
class Color:
	r: int = 0
	g: int = 0
	b: int = 0

	def __str__(self):
		return '({}, {}, {})'.format(self.r, self.g, self.b)

@dataclass
class State:
	enabled: bool = False
	mode: int = 1
	brightness: int = 100
	NUM_COLORS: int = 10
	colors: List[Color] = field(default_factory=list)

	def __str__(self):
		return """
	enabled: {}
	mode: {}
	brightness: {}
	NUM_COLORS: {}
	colors: {}""".format(self.enabled, self.mode, self.brightness, self.NUM_COLORS, [str(c) for c in self.colors])

class DeviceType(Enum):
	USB = 0
	UDP = 1

class SerialCommunicator:
	UDP_PORT = 5568

	def __init__(self, device='/dev/ttyUSB0'):
		self.state = State()
		self.set_device(device)

		for _ in range(self.state.NUM_COLORS):
			self.state.colors.append(Color())
	
	def set_device(self, device):
		if device.startswith('/dev/'):
			self.arduino = Serial(device, 1200)
			self.device_type = DeviceType.USB
		else:
			self.arduino = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			self.device_type = DeviceType.UDP

		self.device_str = device

	def send(self):
		packstring = '=?iii{}B'.format(3 * self.state.NUM_COLORS)
		payload = struct.pack(packstring, self.state.enabled, self.state.mode, self.state.brightness, self.state.NUM_COLORS, *[val for color in map(astuple, self.state.colors) for val in color])

		print('Sending: {}'.format(self.state))

		if self.device_type == DeviceType.USB:
			self.arduino.write(payload)
		else if self.device_type = DeviceType.UDP:
			self.arduino.sendto(payload, self.device_str, UDP_PORT)
		else:
			print('Unknown device type: {}'.format(self.device_type))
	
	def read(self):
		while(self.arduino.in_waiting > 0):
			print(self.arduino.read().decode('utf-8'), end='')

def test():
	a = SerialCommunicator('/dev/ttyUSB0')
	a.send()
	return a