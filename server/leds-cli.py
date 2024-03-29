from ledscomm import CommDevice, Color, State, make_comm_device
import dataclasses
import sys
from typing import Callable, Any
import sys

arg_stack = sys.argv[1:]
arg_stack.reverse()

# TODO: Allow parameters to be named rather than applying them sequentially
def get_input(label: str) -> str:
    if arg_stack:
        value = arg_stack.pop()
        print("{}{}".format(label, value))
        return value
    else:
        return input(label)


def query_for_variable(
    name: str,
    default_value: Any,
    validation_expression: Callable[[int], bool] = lambda x: True,
) -> int:
    while True:
        label = "{:s}[{}]: ".format(name, default_value)
        input_value: str = get_input(label)

        if not input_value:
            return default_value

        if not input_value.lstrip("-").isnumeric():
            continue

        value = int(input_value)

        if validation_expression(value):
            return type(default_value)(value)


device = make_comm_device("192.168.1.237")
# device = Arduino('/dev/ttyUSB0')

state = State(enabled=True, mode=1, brightness=100)

default_color = Color(0, 0, 0)

if True:
    state.enabled = query_for_variable("enabled", True, lambda x: x == 0 or x == 1)
    state.mode = query_for_variable("mode", 1, lambda x: x >= 0)
    state.brightness = query_for_variable("brightness", 100, lambda x: 0 <= x < 256)
    num_colors = query_for_variable("number of colors", 1, lambda x: 0 < x <= 10)

    for i in range(num_colors):
        color = Color()
        color.r = query_for_variable(
            "color_%d.r" % (i), default_color.r, lambda x: 0 <= x < 256
        )
        color.g = query_for_variable(
            "color_%d.g" % (i), default_color.g, lambda x: 0 <= x < 256
        )
        color.b = query_for_variable(
            "color_%d.b" % (i), default_color.b, lambda x: 0 <= x < 256
        )

        state.colors[i] = color

    print()

print(state)

device.state = state

print("sending")
device.send()
print(device.read_ack())
