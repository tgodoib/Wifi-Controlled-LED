#include "Arduino.h"
#include "FastLED.h"

#ifndef BLINK_CPP
#define BLINK_CPP

class Blink {

private:
    bool isOn = false;

public:
    CRGB last[56];

    CRGB *update(int value) {

        for (int i = 0; i < 56; i++) {
            last[i] = CHSV(0, 0, isOn ? 0 : value);
        }

        isOn = !isOn;
        delay(50);

        return last;
    }
};

#endif