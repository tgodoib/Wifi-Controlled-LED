#include "Presets.hpp"

#ifndef RAINBOWMOVING_CPP
#define RAINBOWMOVING_CPP

void RainbowMoving::loop(void show(), int value) {

    for(int i = 0; i < LED_COUNT; i++) {
        if(step == 256) {
            step = 0;
        }

        leds[i] = CHSV(round((i + step) * (255 / (LED_COUNT * 1.5))), 255, value);
    }

    show();

    step++;
    delay(40);
}

#endif