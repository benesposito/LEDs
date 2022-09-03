#if defined(ARDUINO) || defined(ARDUINO2)
    #include "FastLED.h"
#else
    #include "other/colortypes.cpp"
#endif

#define TOTAL_LED_COUNT 300

class LEDStrip {
    private:
        CRGB leds[TOTAL_LED_COUNT];
        unsigned short int led_count;
        float brightness;
    public:
        LEDStrip(int led_count) : led_count(led_count) {};

        void off();
        void solid_rainbow(int hueDelta);
        void digital_snake(CRGB colors[], int num_of_colors, int segment_length);
        void digital_snake2(CRGB colors[], int num_of_colors, int segment_length);
        void analogue_snake(CHSV colors[], int num_of_colors);
        void color_fade(CHSV colors[], int num_of_colors);

        CRGB* getLeds();
        void getLEDCount();
};