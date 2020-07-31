#include "Presets.hpp"

#ifndef COMENGO_CPP
#define COMENGO_CPP

void ComeNGo::loop(void show(), int value) {

    if(loc > LED_COUNT - 1) {
        loc = LED_COUNT - 2;
        isGoing = false;
    }
    if(loc < 0) {
        loc = 1;
        isGoing = true;
    }

    for(int i = 0; i < LED_COUNT; i++) {
        if(i == loc) {
            leds[i] = CHSV(0, 0, value);
        } else {
            leds[i] = CHSV(0, 0, 0);
        }
    }

    show();

    loc += (isGoing ? 1 : -1);
    delay(80);
}

#endif