#include "Presets.hpp"

#ifndef FADING_CPP
#define FADING_CPP

Fading::Fading() {
    count = 1;
}

Fading::Fading(Preset p, CRGB *in, CRGB *fi) {
    finalPreset = p;

    for(int i = 0; i < LED_COUNT; i++) {
        init[i] = in[i];
    }
    for(int i = 0; i < LED_COUNT; i++) {
        final[i] = fi[i];
    }

    current_preset = Preset::FADING;
    count = 1;
}

void Fading::loop(void show()) {

    if(count == 75) {
        current_preset = finalPreset;
    }

    for(int i = 0; i < LED_COUNT; i++) {
        leds[i] = CRGB(
            (int)floor(init[i].r + ((final[i].r - init[i].r) / 75.0f) * count),
            (int)floor(init[i].g + ((final[i].g - init[i].g) / 75.0f) * count),
            (int)floor(init[i].b + ((final[i].b - init[i].b) / 75.0f) * count));
    }

    show();

    count += 1;
    delay(1);
}

#endif