#include "Presets.hpp"

#ifndef RAINBOW_CPP
#define RAINBOW_CPP

void Rainbow::loop(void show(), int value) {

    for(int i = 0; i < LED_COUNT; i++) {
        if(last_hue > 255) {
            last_hue = 0;
        }

        leds[i] = CHSV(last_hue, 255, value);
    }

    show();

    last_hue++;
    delay(60);
}

#endif