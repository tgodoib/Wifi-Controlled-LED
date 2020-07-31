#include "Presets.hpp"

#ifndef RAINBOWSTATIC_CPP
#define RAINBOWSTATIC_CPP

void RainbowStatic::loop(void show(), int value) {
    if(is_first_run) {
        for(int i = 0; i < LED_COUNT; i++) {
            leds[i] = CHSV(round(i * (255 / (LED_COUNT - 1))), 255, value);
        }
        show();
        is_first_run = false;
    }
}

#endif