#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef COMENGO_CPP
#define COMENGO_CPP

ComeNGoPreset::ComeNGoPreset() {
    loc = 0;
    isGoing = 0;
    last_refresh = 0;
}

void ComeNGoPreset::start() {
    last_refresh = millis();
}

void ComeNGoPreset::loop() {
    if(millis() - last_refresh >= 80 || LED::get_force_loop()) {
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
                LED::leds[i] = CHSV(0, 0, LED::value);
            } else {
                LED::leds[i] = CHSV(0, 0, 0);
            }
        }

        LED::show();

        loc += (isGoing ? 1 : -1);
        last_refresh = millis();
    }
}

#endif