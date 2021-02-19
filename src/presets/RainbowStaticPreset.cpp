#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef RAINBOW_STATIC_CPP
#define RAINBOW_STATIC_CPP

RainbowStaticPreset::RainbowStaticPreset() {}

void RainbowStaticPreset::start() {
    for(int i = 0; i < LED_COUNT; i++) {
        LED::leds[i] = CHSV(round(i * (255 / (LED_COUNT - 1))), 255, LED::value);
    }
    LED::show();
}

void RainbowStaticPreset::loop() {
}

#endif