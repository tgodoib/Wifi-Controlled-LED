#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef RAINBOW_MOVING_CPP
#define RAINBOW_MOVING_CPP

RainbowMovingPreset::RainbowMovingPreset() {
    step = 0;
    last_refresh = 0;
}

void RainbowMovingPreset::start() {
    last_refresh = millis();
}

void RainbowMovingPreset::loop() {
    if(millis() - last_refresh >= 40 || LED::get_force_loop()) {
        for(int i = 0; i < LED_COUNT; i++) {
            if(step == 256) {
                step = 0;
            }

            LED::leds[i] = CHSV(round((i + step) * (255 / (LED_COUNT * 1.5))), 255, LED::value);
        }

        LED::show();

        step++;
        last_refresh = millis();
    }
}

#endif