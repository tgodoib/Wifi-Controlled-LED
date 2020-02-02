#include "FastLED.h"

#ifndef SOLID_CPP
#define SOLID_CPP

class Solid {

private:
    CRGB color;

public:
    explicit Solid(CHSV c) {
        color = c;
    }

    explicit Solid(CRGB c) {
        color = c;
    }

    CRGB last[56];

    CRGB *update(int value) {

        for (int i = 0; i < 56; i++) {
            last[i] = color;
        }

        return last;
    }
};

#endif