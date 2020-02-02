#include "Arduino.h"
#include "FastLED.h"

//Presets
#include <presets/Fading.cpp>
#include <presets/Preset.cpp>
#include <presets/blink.cpp>
#include <presets/comeNgo.cpp>
#include <presets/rainbow.cpp>
#include <presets/rainbow_moving.cpp>
#include <presets/rainbow_static.cpp>
#include <presets/solid.cpp>

#ifndef LEDHANDLER_CPP
#define LEDHANDLER_CPP

extern int value;
extern CRGB leds[56];
extern Preset current_preset;
extern CRGB solid_color;

//Preset Instances
extern Fading f;
extern Rainbow r;
extern RainbowStatic rs;
extern RainbowMoving rm;
extern ComeNGo cng;
extern Blink b;

class LED {

public:
    static void setPreset(Preset p, CRGB color = CRGB::White) {
        solid_color = color;
        current_preset = p;

        CRGB init[56];
        for (int i = 0; i < 56; i++) {
            init[i] = leds[i];
        }
        Serial.println("----------");
        loop(false);
        CRGB final[56];
        for (int i = 0; i < 56; i++) {
            final[i] = leds[i];
        }

        f = Fading(p, init, final);
    }

    static void loop(bool update = true) {
        CRGB *temp = leds;

        if (current_preset == Preset::NONE) {
            Solid p = Solid(CRGB(0, 0, 0));
            temp = p.update(value);
        } else if (current_preset == Preset::FADING) {
            temp = f.update(value);
        } else if (current_preset == Preset::SOLID) {
            Solid p = Solid(solid_color);
            temp = p.update(value);
        } else if (current_preset == Preset::RAINBOW) {
            temp = r.update(value);
        } else if (current_preset == Preset::RAINBOW_STATIC) {
            temp = rs.update(value);
        } else if (current_preset == Preset::RAINBOW_MOVING) {
            temp = rm.update(value);
        } else if (current_preset == Preset::COME_N_GO) {
            temp = cng.update(value);
        } else if (current_preset == Preset::BLINK) {
            temp = b.update(value);
        }

        for (int i = 0; i < 56; i++) {
            leds[i] = temp[i];
        }

        if (update)
            FastLED.show();
    }

    static Preset str2enum(String str) {
        if (str == "SOLID") {
            return Preset::SOLID;
        } else if (str == "RAINBOW") {
            return Preset::RAINBOW;
        } else if (str == "RAINBOW_STATIC") {
            return Preset::RAINBOW_STATIC;
        } else if (str == "RAINBOW_MOVING") {
            return Preset::RAINBOW_MOVING;
        } else if (str == "COME_N_GO") {
            return Preset::COME_N_GO;
        } else if (str == "BLINK") {
            return Preset::BLINK;
        }

        return Preset::NONE;
    }
};

#endif