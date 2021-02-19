#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef RAINBOW_CPP
#define RAINBOW_CPP

RainbowPreset::RainbowPreset() {
    last_hue = 0;
    last_refresh = 0;
}

void RainbowPreset::start() {
    last_refresh = millis();
}

void RainbowPreset::loop() {
    if(millis() - last_refresh >= 60 || LED::get_force_loop()) {
        for(int i = 0; i < LED_COUNT; i++) {
            if(last_hue > 255) {
                last_hue = 0;
            }

            LED::leds[i] = CHSV(last_hue, 255, LED::value);
        }

        LED::show();

        last_hue++;
        last_refresh = millis();
    }
}

#endif