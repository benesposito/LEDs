#include "FastLED.h"
#include "LEDStrip.h"

#define LED_COUNT 300
#define DATA 6

float brightness = 1;
float variable_parameter = 1;

LEDStrip led_strip(LED_COUNT);

int mode = 2;
CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)};

void setup() {
    FastLED.setBrightness(100);
	FastLED.addLeds<NEOPIXEL, DATA>(led_strip.getLeds(), LED_COUNT);
}

void loop() {
	switch(mode) {
        case 0:
            led_strip.digital_snake(colors, 3, 2);
            break;
        case 1:
            // analogue_snake((CHSV[]) { CHSV(0, 255, 255), CHSV(0, 0, 255), CHSV(60, 255, 255) });
            break;
        case 2:
            led_strip.solid_rainbow(1);
            break;
    }

    FastLED.show();
    delay(5);
}