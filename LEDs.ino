#include "FastLED.h"
#include "LEDStrip.h"

#define LED_COUNT 300
#define DATA 6

float brightness = 1;
float variable_parameter = 1;

LEDStrip led_strip(LED_COUNT);

int mode = -1;
CRGB colors[6] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255), NULL, NULL, NULL};
int num_colors = 3;

void setup() {
	FastLED.setBrightness(50);
	FastLED.addLeds<NEOPIXEL, DATA>(led_strip.getLeds(), LED_COUNT);

	Serial.begin(4800);
}

void loop() {
	if(Serial.available() > 0) {
		Serial.write(Serial.read());
		// readInput();
		// Serial.println(Serial.readStringUntil(10));
	}

	
	switch(mode) {
		case -1:
			led_strip.off();
			break;
				case 0:
					led_strip.digital_snake(colors, num_colors, 2);
					break;
				case 1:
					// analogue_snake((CHSV[]) { CHSV(0, 255, 255), CHSV(0, 0, 255), CHSV(60, 255, 255) });
					break;
				case 2:
					led_strip.solid_rainbow(1);
					break;
		case 3:
			led_strip.solid_color(CHSV(33, 255, 255));
			break;
		}

		FastLED.show();
	
		//delay(5);
}

// input format: mode;r,g,b,r,g,b,r,g,b,r,g,b,r,g,b,r,g,b,;num_colors;brightness

void readInput() {
	int tmp_mode;
	CRGB tmp_colors[6];
	int tmp_num_colors;
	char c;

	// get mode
	c = getNextChar();
	Serial.print("Next char: ");
	Serial.println(c);
	if(isdigit(c)) {
		tmp_mode = ctoi(c);
		Serial.print("Mode: ");
		Serial.println(tmp_mode);
	} else {
		terminateRead("Mode is not a digit!");
		return;
	}

	// check semicolon
	c = getNextChar();
	Serial.print("Next char: ");
	Serial.println(c);
	if(c == ';')
		Serial.println("Mode finished.");
	else {
		terminateRead("No semicolon following mode!");
		return;
	}

	// get colors
	for(int i = 0; i < 1; i++) {
		int rgb[3] = {0, 0, 0};

		for(int j = 0; j < 3; j++) {
			c = getNextChar();
			Serial.print("Next char: ");
			Serial.println(c);
			while(c != ',') {
				if(isdigit(c)) {
					Serial.print("Read value: ");
					Serial.println(c);
					rgb[j] = rgb[j] * 10 + ctoi(c);
				}
				else {
					Serial.println((int) c);
					terminateRead("Above ASCII value was not expected in RGB input.");
					return;
				}

				c = getNextChar();
				Serial.print("Next char: ");
				Serial.println(c);
			}

			Serial.print(j);
			Serial.print(" is: ");
			Serial.println(rgb[j]);
		}

		Serial.print("Color #");
		Serial.print(i + 1);
		Serial.println(" is done.");
	}

	// check semicolon
	c = getNextChar();
	Serial.print("Next char: ");
	Serial.println(c);
	if(c == ';')
		Serial.println("Mode finished.");
	else {
		terminateRead("No semicolon following mode!");
		return;
	}
	
	c = getNextChar();
	Serial.print("Next char: ");
	Serial.println(c);
	if(c == 10)
		Serial.println("Success!");
	else {
		terminateRead("Message did not exit properly");
		return;
	}

	mode = tmp_mode;
	memcpy(colors, tmp_colors, sizeof(colors));
	num_colors = tmp_num_colors;
}

void terminateRead(String message) {
	Serial.println("Terminating: " + message);

	// if(Serial.available() > 0)
	// 	while(Serial.read() != 10) { }

	while(Serial.available() > 0)
		Serial.read();

	Serial.print("Finished terminating, ");
	Serial.print(Serial.available());
	Serial.println(" bytes remaining.");
}

int ctoi(char c) {
	return c - '0';
}

char getNextChar() {
	unsigned long begin = millis();

	while(Serial.available() == 0) {
		if(millis() - begin > 1000) {
			Serial.println("Waited one second without new input");
			break;
		}
	}

	return Serial.read();
}