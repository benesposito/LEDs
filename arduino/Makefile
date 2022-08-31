uno_fqbn := arduino:avr:uno
nodemcu_fqbn := esp8266:esp8266:nodemcuv2

# PLATFORM can be 'uno' or 'nodemcu'
PLATFORM := nodemcu
PORT := /dev/ttyUSB0

esp_options := baud=921600

compile:
	arduino-cli compile --fqbn $($(PLATFORM)_fqbn) .

compile_all:
	make compile PLATFORM=uno
	make compile PLATFORM=nodemcu

upload: compile
	arduino-cli upload -p $(PORT) --fqbn $($PLATFORM_fqbn):$(esp_options) .
