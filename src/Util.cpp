#include "FastLED.h"
#include "debug/Debug.hpp"
#include <Arduino.h>
#include <LedConstants.h>

#ifndef UTIL_CPP
#define UTIL_CPP

class Util {

public:
    static String valueFromStr(String data, char separator, int index) {
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length() - 1;

        for(int i = 0; i <= maxIndex && found <= index; i++) {
            if(data.charAt(i) == separator || i == maxIndex) {
                found++;
                strIndex[0] = strIndex[1] + 1;
                strIndex[1] = (i == maxIndex) ? i + 1 : i;
            }
        }

        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
    }

    static CRGB fixValue(CRGB color, float v) {

        CRGB color_final;

        float max = 0;
        if(color.r > max) {
            max = color.r;
        }
        if(color.g > max) {
            max = color.g;
        }
        if(color.b > max) {
            max = color.b;
        }

        float ratio = (max > 0.0 ? v / max : 0.0);
        color_final = CRGB(color.r * ratio, color.g * ratio, color.b * ratio);

        return color_final;
    }
};

#endif