#ifndef STATE_H
#define STATE_H

#include <FastLED.h>

#define MAX_NUM_COLORS 10

struct state {
    bool enabled;
    uint8_t mode;
    uint8_t brightness;
    uint8_t NUM_COLORS;
    CRGB colors[MAX_NUM_COLORS];
};

#endif /* STATE_H */