#include "FastLED.h"

#ifndef RAINBOWSTATIC_CPP
#define RAINBOWSTATIC_CPP

class RainbowStatic {

public:

    CRGB last[56];

    CRGB *update(int value) {

        for (int i = 0; i < 56; i++) {
            last[i] = CHSV(round(i * (255 / 55)), 255, value);
        }
    
        return last;
    }
};

#endif