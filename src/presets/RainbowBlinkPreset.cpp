#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef RAINBOW_BLINK_CPP
#define RAINBOW_BLINK_CPP

RainbowBlinkPreset::RainbowBlinkPreset() {
    color = 0;
    last_refresh = 0;
}

void RainbowBlinkPreset::start() {
    last_refresh = millis();
}

void RainbowBlinkPreset::loop() {
    if(millis() - last_refresh >= 333 || LED::get_force_loop()) {
        for(int i = 0; i < LED_COUNT; i++) {
            LED::leds[i] = CHSV(color, 255, LED::value);
        }

        color += 32;
        if(color > 255) {
            color = 0;
        }

        LED::show();
        last_refresh = millis();
    }
}

#endif