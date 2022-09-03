#define ARDUINO2
#include "LEDStrip.h"
#include "Arduino.h" // figure out how to not require this include

#define LED_COUNT 300
#define DATA 6

float brightness = 1;
float variable_parameter = 1;

LEDStrip led_strip(LED_COUNT);

int mode = 1;
CRGB colors[] = {CRGB(255, 10, 10), CRGB::Green};

void setup() {
    Serial.begin(9600);

    FastLED.setBrightness(155);
	FastLED.addLeds<NEOPIXEL, DATA>(led_strip.getLeds(), LED_COUNT);
}

void loop() {
	switch(mode) {
        case 0:
            led_strip.off();
            break;
        case 1:
            led_strip.digital_snake(colors, 2, 10);
            delay(20);
            break;
        case 2:
            // analogue_snake((CHSV[]) { CHSV(0, 255, 255), CHSV(0, 0, 255), CHSV(60, 255, 255) });
            break;
        case 3:
            led_strip.solid_rainbow(1);
        delay(15);
            break;
    }

    FastLED.show();
}