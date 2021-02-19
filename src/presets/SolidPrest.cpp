#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef SOLID_CPP
#define SOLID_CPP

SolidPreset::SolidPreset(CHSV c) {
    solid_color = c;
}

void SolidPreset::set_color(CHSV c) {
    LED::value = c.v;
    solid_color = c;
}

CHSV SolidPreset::get_color() {
    return solid_color;
}

void SolidPreset::start() {
    // solid_color.v = LED::value;
    for(int i = 0; i < LED_COUNT; i++) {
        LED::leds[i] = solid_color;
    }
    LED::show();
}

void SolidPreset::loop() {}

#endif