#include <iostream>
#include "FastLED.h"
#include "LEDStrip.h"

#define ITERATIONS 1000

float brightness = 1;
float variable_parameter = 0.1;

CRGB leds[LED_COUNT];
CRGB simulation[LED_COUNT][ITERATIONS];

int main() {
    CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)};
    
    std::cout << "var simulation = [" << std::endl;
    for(int i = 0; i < ITERATIONS; i++) {
        digital_snake(colors, 3, 2);
        std::cout << "[" << std::endl;
        
        for(int j = 0; j < LED_COUNT; j++)
            std::cout << "\"rgb(" << leds[j].r << ", " << leds[j].g << ", " << leds[j].b << ")\"," << std::endl;

        std::cout << "]," << std::endl;
    }

    std::cout << "]" << std::endl;
}

void solid_rainbow() {
    const int MAX_HUE_DELTA = 30;
    static int hue = 0;
    
    for(int i = 0; i < LED_COUNT; i++)
        leds[i].setHSV(hue, 255, brightness * 255);

    hue += variable_parameter * MAX_HUE_DELTA;
    
    if(hue > 360)
        hue -= 360;
}

void digital_snake(CRGB colors[], int num_of_colors, int segment_length) {
    static int first_color_index = 0;
    int color_index = first_color_index;

    int segments = LED_COUNT / segment_length;

    for(int i = 0; i < segments; i++) {
        for(int j = 0; j < segment_length; j++) {
            leds[i * segment_length + j] = colors[color_index];
        }

        ++color_index %= num_of_colors;
    }
    
    for(int i = 0; i < LED_COUNT % segment_length; i++)
        leds[LED_COUNT - segment_length + i] = colors[color_index];

    first_color_index--;
    if(first_color_index < 0)
        first_color_index = num_of_colors - 1;
}