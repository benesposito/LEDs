PLATFORM = esp8266:esp8266:nodemcuv2
PORT = /dev/ttyUSB0

ESP_OPTIONS=baud=921600

compile:
	arduino-cli compile --fqbn $(PLATFORM) .

upload: compile
	arduino-cli upload -p $(PORT) --fqbn $(PLATFORM):$(ESP_OPTIONS) .
