#include "Arduino.h"
#include "FastLED.h"

#ifndef RAINBOWMOVING_CPP
#define RAINBOWMOVING_CPP

class RainbowMoving {

private:
    int step = 0;

public:
    CRGB last[56];

    CRGB *update(int value) {

        for (int i = 0; i < 56; i++) {
            if (step == 256) {
                step = 0;
            }

            last[i] = CHSV(round((i + step) * (255 / 80)), 255, value);
        }

        step++;

        delay(40);

        return last;
    }
};

#endif