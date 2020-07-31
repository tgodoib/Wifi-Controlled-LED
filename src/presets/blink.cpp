#include "Presets.hpp"

#ifndef BLINK_CPP
#define BLINK_CPP

void Blink::loop(void show(), int value) {

    for(int i = 0; i < LED_COUNT; i++) {
        leds[i] = CHSV(0, 0, isOn ? 0 : value);
    }

    show();

    isOn = !isOn;
    delay(50);
}

#endif