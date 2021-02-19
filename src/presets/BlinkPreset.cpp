#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef BLINK_CPP
#define BLINK_CPP

BlinkPreset::BlinkPreset() {
    isOn = false;
    last_refresh = 0;
}

void BlinkPreset::start() {
    last_refresh = millis();
}

void BlinkPreset::loop() {
    if(millis() - last_refresh >= 80 || LED::get_force_loop()) {
        for(int i = 0; i < LED_COUNT; i++) {
            LED::leds[i] = CHSV(0, 0, isOn ? 0 : LED::value);
        }

        LED::show();

        isOn = !isOn;
        last_refresh = millis();
    }
}

#endif