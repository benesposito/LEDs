#include <FastLED.h>
#include "LEDStrip.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define LED_COUNT 300
#define DATA_PIN 5

#define MAX_NUM_COLORS 10

#define UDP_PORT 5568

struct state_s {
	bool enabled;
	uint8_t mode;
	uint8_t brightness;
	uint8_t NUM_COLORS;
	CRGB colors[MAX_NUM_COLORS];
};

struct state_s state;
WiFiUDP udp;
LEDStrip led_strip(LED_COUNT);

void setup() {
	Serial.begin(1200);
	WiFi.begin("Chestnut Square", "8884Pavlov");

	while(WiFi.status() != WL_CONNECTED) {
		char output[64];
		snprintf(output, sizeof(output), "Connecting... [%d]\n", WiFi.status());
		Serial.print(output);
		delay(500);
	}

	int ret = udp.begin(1111);

	Serial.println("Connected!");
	Serial.println(WiFi.localIP());

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_strip.getLeds(), LED_COUNT);
	FastLED.setBrightness(10);

	state.enabled = true;
	state.mode = 1;
	state.brightness = 100;
	state.NUM_COLORS = MAX_NUM_COLORS;
	state.colors[0] = CRGB(0, 0, 255);
}

void loop() {	
	check_for_new_state();

	char state_info[256];
	snprintf(state_info, sizeof(state_info), "(%d, %d, %d)\n", state.enabled, state.mode, state.brightness);
	Serial.print(state_info);

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

	delay(1000);
}

void check_for_new_state() {
	int packet_size = udp.parsePacket();
	
	if(udp.available()) {
		udp.read((uint8_t *) &state, sizeof(state));

		udp.beginPacket(udp.remoteIP(), udp.remotePort());
		udp.write(0);
		udp.endPacket();
	} else if(Serial.available() == sizeof(state)) {
		Serial.readBytes((uint8_t *) &state, sizeof(state));
		Serial.write(0);
	} else if(Serial.available() > 0) {
		Serial.write(1);
	}
}