#include "FastLED.h"
#include "LEDStrip.h"

#define LED_COUNT 300
#define DATA 5

#define MAX_NUM_COLORS 10

struct COLOR {
	uint8_t r, g, b;
};

struct {
	bool enabled;
	long int mode;
	long int brightness;
	long int NUM_COLORS;
	CRGB colors[MAX_NUM_COLORS];
} state;

LEDStrip led_strip(LED_COUNT);

void setup() {
	FastLED.setBrightness(10);
	FastLED.addLeds<NEOPIXEL, DATA>(led_strip.getLeds(), LED_COUNT);

	Serial.begin(1200);

	state.enabled = true;
	state.mode = 1;
	state.brightness = 100;
	state.NUM_COLORS = MAX_NUM_COLORS;
	state.colors[0] = CRGB(0, 0, 255);

	Serial.println(sizeof(state));
}

void loop() {
	char buff[256];
	sprintf(buff, "Color 0: %d,%d,%d", state.colors[0].r, state.colors[0].g, state.colors[0].b);
	Serial.println(buff);
	
	check_for_new_state();

	if(state.enabled) {
		switch(state.mode) {
			// mode 0 is not used as a 'disabled' mode because I wanted to preserve the previously selected mode
			case 1:
				led_strip.solid_color(state.colors[0]);
				break;
			case 2:
				led_strip.solid_rainbow(1);
				break;
			case 3:
				led_strip.digital_snake(state.colors, state.NUM_COLORS, 2);
				break;
		}
	} else {
		led_strip.off();
	}
	
	FastLED.show();
}

void check_for_new_state() {
	if(Serial.available() == sizeof(state)) {
		Serial.readBytes((uint8_t *) &state, sizeof(state));
		respond(0);
	} else if(Serial.available() > 0) {
		respond(1);
	}
}

void respond(uint8_t errcode) {
	Serial.write(errcode);
}