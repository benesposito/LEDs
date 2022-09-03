#include <iostream>
#include "../LEDStrip.h"

#define LED_COUNT 30
#define ITERATIONS 1000

float brightness = 1;
float variable_parameter = 0.1;

LEDStrip led_strip(LED_COUNT);
CRGB simulation[LED_COUNT][ITERATIONS];

void print_leds();

int main() {
    std::cout << "var simulation = [" << std::endl;

    CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)};
    
    for(int i = 0; i < ITERATIONS; i++) {
        led_strip.digital_snake(colors, 3, 4);
        print_leds();
    }

    std::cout << "]" << std::endl;
}

void print_leds() {
    std::cout << "[" << std::endl;
    
    for(int i = 0; i < LED_COUNT; i++)
        std::cout << "\"rgb(" << led_strip.getLeds()[i].r << ", " << led_strip.getLeds()[i].g << ", " << led_strip.getLeds()[i].b << ")\"," << std::endl;

    std::cout << "]," << std::endl;
}