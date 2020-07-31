#include "Presets.hpp"

#ifndef SOLID_CPP
#define SOLID_CPP

Solid::Solid() {
}

Solid::Solid(CHSV c) {
    color = c;
    hsv2rgb_rainbow(color, rgb_color);
}

void Solid::loop(void show()) {
    fill_solid(leds, LED_COUNT, rgb_color);
    show();
    should_update_strip = false;
}

#endif