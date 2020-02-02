#include "Arduino.h"
#include "FastLED.h"

#ifndef RAINBOW_CPP
#define RAINBOW_CPP


class Rainbow {

public:

    CHSV last[56];  

    CRGB *update(int value) {

        CRGB temp[56];

        for (int i = 0; i < 56; i++) {
            if (last[i].h < 255) {
                temp[i] = CHSV(last[i].h += 1, 255, value);
            } else {
                temp[i] = CHSV(0, 255, value);
            }
        }

        delay(60);

        return temp;
    }
};

#endif