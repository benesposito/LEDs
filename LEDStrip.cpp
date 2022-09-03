#include "LEDStrip.h"
// #include <iostream>

void LEDStrip::off() {
    for(int i = 0; i < led_count; i++)
        leds[i] = CRGB(0, 0, 0);
}

void LEDStrip::digital_snake(CRGB colors[], int num_of_colors, int segment_length) {
    static int shifter = 0;
    static int color_index = 0;
    int original_color_index = color_index;

    for(int led_index = 0; led_index < led_count; led_index++) {
        leds[led_index] = colors[color_index];
        
        if(led_index % segment_length == shifter)
            ++color_index %= num_of_colors;
    }

    if(++shifter % segment_length == 0) {
        shifter = 0;
        
        if(original_color_index == 0)
            color_index = num_of_colors - 1;
        else
            color_index = original_color_index - 1;
        
    } else
        color_index = original_color_index;
}

void LEDStrip::analogue_snake(CHSV colors[], int num_of_colors) {
    static int first_led_index = 0;
    const int wavelength = led_count;
    
    
}

void LEDStrip::color_fade(CHSV colors[], int num_of_colors) {
    // const int wavelength = led_count;

    for(int i = 0; i < num_of_colors; i++) {
        for(int j = 0; j < led_count / num_of_colors; j++) {
            
        }
    }
}

void LEDStrip::solid_rainbow(int hueDelta) {
    static int hue = 0;
    
    for(int i = 0; i < led_count; i++)
        leds[i].setHSV(hue, 255, 255);

    hue += hueDelta;
    
    if(hue >= 255)
        hue -= 255;
}

CRGB* LEDStrip::getLeds() {
    return leds;
}