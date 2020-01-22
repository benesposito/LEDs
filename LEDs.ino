#include "FastLED.h"
#include "LEDStrip.h"

#define LED_COUNT 300
#define DATA 6

#define MAX_NUM_COLORS 6

float brightness = 1;
float variable_parameter = 1;

LEDStrip led_strip(LED_COUNT);

bool enabled = false;
int mode = -1;
CRGB colors[MAX_NUM_COLORS] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255), NULL, NULL, NULL};
int num_colors = 3;

void setup() {
	FastLED.setBrightness(50);
	FastLED.addLeds<NEOPIXEL, DATA>(led_strip.getLeds(), LED_COUNT);

	Serial.begin(1200);
}

void loop() {
	if(Serial.available())
		readInput(false);

	if(enabled) {
		switch(mode) {
			case 1:
				led_strip.digital_snake(colors, num_colors, 2);
				break;
			case 2:
				led_strip.solid_rainbow(1);
				break;
			case 3:
				led_strip.solid_color(colors[0]);
				break;
		}
	} else {
		led_strip.off();
	}

	FastLED.show();
}

// input format: mode;num_colors;r,g,b,r,g,b,r,g,b,r,g,b,r,g,b,r,g,b,;brightness

void readInput(bool print_status) {
	int tmp_mode, tmp_num_colors, tmp_brightness;
	CRGB tmp_colors[6];
	char c;

	// get mode
	c = getNextChar();

	if(isdigit(c)) {
		tmp_mode = ctoi(c);
		
		if(print_status) {
			Serial.print("Mode: ");
			Serial.println(tmp_mode);
		}
	} else {
		terminateRead("Mode is not a digit!");
		return;
	}

	// check semicolon
	c = getNextChar();
	
	if(c == ';') {
		if(print_status)
			Serial.println("Mode finished.");
	} else {
		terminateRead("No semicolon following mode!");
		return;
	}
	
	unsigned long start = millis();
	while(Serial.available() == 0 && millis() - start < 100) { }
	c = getNextChar();

	if(c == 10) {
		enabled = tmp_mode;
		
		if(print_status) {
			Serial.println("Only mode, therefore it is being read as enabled");
		}
	} else {
		// get brightness & check semicolon

		tmp_brightness = 0;

		while(c != ';') {
			if(isdigit(c))
				tmp_brightness = tmp_brightness * 10 + ctoi(c);
			else {
				Serial.println((int) c);
				terminateRead("Above ASCII value was not expected in RGB input.");
				return;
			}

			c = getNextChar();
		}

		// get num_colors
		c = getNextChar();

		if(isdigit(c)) {
			tmp_num_colors = ctoi(c);
			
			if(print_status) {
				Serial.print("num_colors: ");
				Serial.println(tmp_num_colors);
			}
		} else {
			terminateRead("num_colors is not a digit!");
			return;
		}

		if(tmp_num_colors > MAX_NUM_COLORS)
			tmp_num_colors = MAX_NUM_COLORS;

		// check semicolon
		c = getNextChar();
		
		if(c == ';') {
			if(print_status)
				Serial.println("Mode finished.");
		} else {
			terminateRead("No semicolon following mode!");
			return;
		}

		// get colors
		for(int i = 0; i < tmp_num_colors; i++) {
			int rgb[3] = {0, 0, 0};

			for(int j = 0; j < 3; j++) {
				c = getNextChar();

				while(c != ',') {
					if(isdigit(c))
						rgb[j] = rgb[j] * 10 + ctoi(c);
					else {
						Serial.println((int) c);
						terminateRead("Above ASCII value was not expected in RGB input.");
						return;
					}

					c = getNextChar();
				}
			}

			tmp_colors[i] = CRGB(rgb[0], rgb[1], rgb[2]);

			// Serial.print("Color #");
			// Serial.print(i + 1);
			// Serial.print(" is (");
			// Serial.print(rgb[0]);
			// Serial.print(", ");
			// Serial.print(rgb[1]);
			// Serial.print(", ");
			// Serial.print(rgb[2]);
			// Serial.println(").");
		}

		// check semicolon
		c = getNextChar();
		
		if(c == ';') {
			if(print_status)
				Serial.println("Colors finished.");
		}
		else {
			terminateRead("No semicolon following Colors!");
			return;
		}
		
		c = getNextChar();
		
		if(c == 10) {
			if(print_status)
				Serial.println("Success!");
		} else {
			terminateRead("Message did not exit properly");
			return;
		}

		mode = tmp_mode;
		brightness = tmp_brightness;
		num_colors = tmp_num_colors;
		memcpy(colors, tmp_colors, sizeof(colors));

		FastLED.setBrightness(brightness * 255.0 / 100.0);
	}
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
