from enum import Enum
from dataclasses import dataclass, field, astuple
from typing import List, Tuple
import struct
from serial import Serial
import socket

@dataclass
class Color:
	r: int = 0
	g: int = 0
	b: int = 0

@dataclass
class State:
	enabled: bool = False
	mode: int = 1
	brightness: int = 100
	_NUM_COLORS: int = 10
	colors: Tuple[Color, ...] = (Color(),) * _NUM_COLORS

class Device:
	def write(self, payload):
		raise NotImplementedError()

	def read(self):
		raise NotImplementedError()

class USBDevice(Device):
	BAUD_RATE = 1200

	def __init__(self, port: str):
		self.io = Serial(port, USBDevice.BAUD_RATE)

	def write(self, payload):
		self.io.write(payload)

	def read(self):
		while self.io.in_waiting <= 0:
			return self.io.read()


class UDPDevice(Device):
	UDP_PORT = 1111

	def __init__(self, ip: str):
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.socket.connect((ip, UDPDevice.UDP_PORT))

	def write(self, payload: bytes):
		return self.socket.send(payload)

def _is_valid_ip(ip: str) -> bool:
	subnets = ip.split('.')
	return len(subnets) == 4 and all(0 < int(subnet) < 256 for subnet in subnets)

class Arduino:
	def __init__(self, ip_or_port: str):
		self.state = State()

		if _is_valid_ip(ip_or_port):
			self.device = UDPDevice(ip_or_port)
		else:
			self.device = USBDevice(ip_or_port)

	def send(self):
		packstring = '=?BBB{}B'.format(3 * self.state._NUM_COLORS)
		payload = struct.pack(packstring, self.state.enabled, self.state.mode, self.state.brightness, self.state._NUM_COLORS, *[val for color in map(astuple, self.state.colors) for val in color])

		return self.device.write(payload)

	def read(self):
		return self.device.read()

	def __str__(self):
		return str(self.state)