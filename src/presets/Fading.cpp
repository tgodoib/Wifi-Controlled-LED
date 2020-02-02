#include "Arduino.h"
#include "FastLED.h"
#include "presets/Preset.cpp"

#ifndef FADING_CPP
#define FADING_CPP

extern CRGB leds[56];
extern Preset current_preset;
extern CRGB solid_color;

class Fading {

private:
    Preset finalPreset;
    CRGB init[56];
    CRGB final[56];
    int count;

public:
    explicit Fading() {
        count = 1;
    }

    explicit Fading(Preset p, CRGB *in, CRGB *fi) {
        finalPreset = p;

        for (int i = 0; i < 56; i++) {
            init[i] = in[i];
        }
        for (int i = 0; i < 56; i++) {
            final[i] = fi[i];
        }

        current_preset = Preset::FADING;
        count = 1;
        Serial.println("Ended Setup");
    }

    CRGB *update(int value) {
        CRGB colors[56];

        if (count == 300) {
            current_preset = finalPreset;
        }

        for (int i = 0; i < 56; i++) {

            colors[i] = CRGB(
                (int)floor(init[i].r + ((final[i].r - init[i].r) / 300.0f) * count),
                (int)floor(init[i].g + ((final[i].g - init[i].g) / 300.0f) * count),
                (int)floor(init[i].b + ((final[i].b - init[i].b) / 300.0f) * count));

            //Serial.println("----");
        }

        count += 1;
        delay(1);

        //Serial.println("-----");
        return colors;
    }
};

#endif