#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "LEDStrip.h"
#include "comm.h"
#include "state.h"

#include <FastLED.h>

#define LED_COUNT 50
#define DATA_PIN D8

#define UDP_PORT 5568

#ifdef ESP8266
comm_wifi* communicator;
#else
comm_serial* communicator;
#endif

struct state state = {
    .enabled = true,
    .mode = 1,
    .brightness = 100,
    .NUM_COLORS = MAX_NUM_COLORS,
    .colors = {CRGB(100, 100, 255)},
};

bool new_state;
LEDStrip led_strip(LED_COUNT);

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(led_strip.getLeds(), LED_COUNT);

#ifdef ESP8266
    communicator = new comm_wifi{};
#else
    communicator = new comm_serial{};
#endif

    communicator->begin();

    size_t last_print = 0;
    while (!communicator->ready()) {
        led_strip.fade(state.colors[0], 1);
        FastLED.show();

        if (millis() - last_print > 500) {
            char output[64];
            snprintf(output, sizeof(output), "Connecting... [%d]\n",
                     communicator->status());
            Serial.print(output);
            last_print = millis();
        }
    }

#ifdef ESP8266
    Serial.println(static_cast<comm_wifi*>(communicator)->ip());
#endif

    update_strip();
}

void loop() {
    new_state = check_for_new_state();

    if (new_state) {
        update_strip();
    }
}

void update_strip() {
    char state_info[256];
    snprintf(state_info, sizeof(state_info), "(%d, %d, %d, (%d, %d, %d))\n",
             state.enabled, state.mode, state.brightness, state.colors[0].red,
             state.colors[0].green, state.colors[0].blue);
    Serial.print(state_info);

    if (state.enabled) {
        switch (state.mode) {
        // mode 0 is not used as a 'disabled' mode because I wanted to
        // preserve the previously selected mode
        case 1:
            led_strip.solid_color(state.colors[0]);
            break;
        case 2:
            led_strip.solid_rainbow(1);
            break;
        case 3:
            led_strip.digital_snake(state.colors, state.NUM_COLORS, 2);
            break;
        case 4:
            led_strip.fade(state.colors[0], 10);
            break;
        }
    } else {
        led_strip.off();
    }

    FastLED.setBrightness(state.brightness);
    FastLED.show();
}

bool check_for_new_state() {
    communicator->update();

    if (communicator->state_available()) {
        communicator->read_state(&state);
        communicator->write_ack(1);
        return true;
    } else if (communicator->available() > 0) {
        communicator->clear_read_buffer();
        communicator->write_ack(0);
        return false;
    }

    return false;
}
