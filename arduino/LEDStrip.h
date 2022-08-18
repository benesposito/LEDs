#include <FastLED.h>

#define TOTAL_LED_COUNT 300

class LEDStrip {
private:
    CRGB leds[TOTAL_LED_COUNT];
    unsigned short int led_count;
    float brightness;

public:
    LEDStrip(int led_count) : led_count(led_count){};

    void off();
    void solid_color(CRGB color);
    void solid_rainbow(int hueDelta);
    void digital_snake(CRGB colors[], int num_of_colors, int segment_length);
    void analogue_snake(CHSV colors[]);
    void color_fade(CHSV colors[]);
    CRGB* getLeds();
    void getLEDCount();
};
