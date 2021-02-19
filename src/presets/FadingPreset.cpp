#include "Presets.hpp"
#include "handlers/LedHandler.hpp"

#ifndef FADING_CPP
#define FADING_CPP

FadingPreset::FadingPreset() {}

FadingPreset::FadingPreset(PresetType p, CRGB *in, CRGB *fi) {
    FadingPreset::finalPreset = p;
    for(int i = 0; i < LED_COUNT; i++) {
        init[i] = in[i];
    }
    for(int i = 0; i < LED_COUNT; i++) {
        final[i] = fi[i];
    }
    FadingPreset::count = 1;
}

void FadingPreset::start() {
    LED::current_preset = LED::preset_list[PresetType::FADING];
}

void FadingPreset::loop() {
    if(count == 75) {
        LED::setPreset(finalPreset, false);
    }

    for(int i = 0; i < LED_COUNT; i++) {
        LED::leds[i] = CRGB(
            (int)floor(init[i].r + ((final[i].r - init[i].r) / 75.0f) * count),
            (int)floor(init[i].g + ((final[i].g - init[i].g) / 75.0f) * count),
            (int)floor(init[i].b + ((final[i].b - init[i].b) / 75.0f) * count));

        // LED::leds[i] = init[i];
    }

    LED::show();

    count += 1;
    delay(1);
}

#endif