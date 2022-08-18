#include "LEDStrip.h"

void LEDStrip::off() {
    for (int i = 0; i < led_count; i++)
        leds[i] = CRGB::Black;
}

void LEDStrip::solid_color(CRGB color) {
    // Serial.print(color.r);
    // Serial.print(",");
    // Serial.print(color.g);
    // Serial.print(",");
    // Serial.println(color.b);
    for (int i = 0; i < led_count; i++)
        leds[i] = color;
}

void LEDStrip::digital_snake(CRGB colors[], int num_of_colors,
                             int segment_length) {
    static int first_color_index = 0;

    int color_index = first_color_index;
    int segments = led_count / segment_length;

    for (int i = 0; i < segments; i++) {
        for (int j = 0; j < segment_length; j++) {
            leds[i * segment_length + j] = colors[color_index];
        }

        ++color_index %= num_of_colors;
    }

    for (int i = 0; i < led_count % segment_length; i++)
        leds[led_count - segment_length + i] = colors[color_index];

    first_color_index--;
    if (first_color_index < 0)
        first_color_index = num_of_colors - 1;
}

void LEDStrip::analogue_snake(CHSV colors[]) {
    static int first_led_index = 0;
    const int colors_length = sizeof(colors) / sizeof(CRGB);
    const int wavelength = led_count;
}

void LEDStrip::color_fade(CHSV colors[]) {
    const int colors_length = sizeof(colors) / sizeof(CHSV);
    // const int wavelength = led_count;

    for (int i = 0; i < colors_length; i++) {
        for (int j = 0; j < led_count / colors_length; j++) {
        }
    }
}

void LEDStrip::solid_rainbow(int hueDelta) {
    static int hue = 0;

    for (int i = 0; i < led_count; i++)
        leds[i].setHSV(hue, 255, 255);

    hue += hueDelta;

    if (hue > 360)
        hue -= 360;
}

CRGB* LEDStrip::getLeds() { return leds; }
