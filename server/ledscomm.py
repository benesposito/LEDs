from enum import Enum
from dataclasses import dataclass, field, astuple
from typing import List
import struct
from serial import Serial
import socket
from abc import ABC, abstractmethod

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

class CommDevice(ABC):
	def __init__(self):
		self.state = State()

	@abstractmethod
	def _write(self, payload: bytes) -> int:
		return

	def send(self) -> int:
		payload: bytes = self._create_payload()
		return self._write(payload)

	@abstractmethod
	def read(self) -> bytes:
		return

	def read_ack(self) -> int:
		return int.from_bytes(self.read(), byteorder='little', signed=True)

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

	def __str__(self) -> str:
		return str(self.state)

class USBDevice(CommDevice):
	BAUD_RATE = 1200

	def __init__(self, port: str):
		super().__init__()
		self.io = Serial(port, USBDevice.BAUD_RATE)

	def _write(self, payload: bytes) -> int:
		return self.io.write(payload)

	# TODO: fix this function, this is wrong
	def read(self) -> bytes:
		while self.io.in_waiting <= 0:
			return self.io.read()

class UDPDevice(CommDevice):
	UDP_PORT = 1111

	def __init__(self, ip: str):
		super().__init__()
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.socket.connect((ip, UDPDevice.UDP_PORT))

	def _write(self, payload: bytes) -> int:
		return self.socket.send(payload)

	def read(self) -> bytes:
		return self.socket.recv(1024)

def _is_valid_ip(ip: str) -> bool:
	subnets = ip.split('.')
	return len(subnets) == 4 and all(0 < int(subnet) < 256 for subnet in subnets)

def make_comm_device(ip_or_port: str):
	if _is_valid_ip(ip_or_port):
		return UDPDevice(ip_or_port)
	else:
		return USBDevice(ip_or_port)
