#include "Arduino.h"
#include "FastLED.h"

#ifndef COMENGO_CPP
#define COMENGO_CPP

class ComeNGo {

private:
    int loc = 0;
    bool isGoing = true;

public:
    CRGB last[56];

    CRGB *update(int value) {

        if (loc > 55) {
            loc = 54;
            isGoing = false;
        }
        if (loc < 0) {
            loc = 1;
            isGoing = true;
        }

        for (int i = 0; i < 56; i++) {
            if (i == loc) {
                last[i] = CHSV(0, 0, value);
            } else {
                last[i] = CHSV(0, 0, 0);
            }
        }

        loc += (isGoing ? 1 : -1);
        delay(80);

        return last;
    }
};

#endif