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

@dataclass
class State:
	enabled: bool = False
	mode: int = 1
	brightness: int = 100
	_NUM_COLORS: int = 10
	colors: List[Color] = field(default_factory=list)

class Device:
	def write(self, payload: bytes) -> int:
		raise NotImplementedError()

	def read(self) -> int:
		raise NotImplementedError()

class USBDevice(Device):
	BAUD_RATE = 1200

	def __init__(self, port: str):
		self.io = Serial(port, USBDevice.BAUD_RATE)

	def write(self, payload: bytes) -> int:
		return self.io.write(payload)

	def read(self) -> int:
		while self.io.in_waiting <= 0:
			return self.io.read()


class UDPDevice(Device):
	UDP_PORT = 1111

	def __init__(self, ip: str):
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.socket.connect((ip, UDPDevice.UDP_PORT))

	def write(self, payload: bytes) -> int:
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

	def _create_payload(self) -> bytes:
		packstring: str = '=?BBB{}B'.format(3 * self.state._NUM_COLORS)
		colors: list = list()

		for i in range(min(len(self.state.colors), self.state._NUM_COLORS)):
			colors.append(self.state.colors[i])
		
		for i in range(self.state._NUM_COLORS - len(self.state.colors)):
			colors.append(Color())
		
		payload: bytes = struct.pack(
			packstring,
			self.state.enabled,
			self.state.mode,
			self.state.brightness,
			self.state._NUM_COLORS,
			*[color for color in map(astuple, colors) for color in color]
		)

		return payload

	def send(self) -> int:
		payload: bytes = self._create_payload()
		return self.device.write(payload)

	def read(self) -> int:
		return self.device.read()

	def __str__(self) -> str:
		return str(self.state)