#include "Presets.hpp"

#ifndef RAINBOW_BLINK_CPP
#define RAINBOW_BLINK_CPP

void RainbowBlink::loop(void show(), int value) {

    for(int i = 0; i < LED_COUNT; i++) {
        leds[i] = CHSV(color, 255, value);
    }

    color += 32;
    if(color > 255) {
        color = 0;
    }

    show();

    delay(333);
}

#endif