#include "Arduino.h"
#include "FastLED.h"

//Presets
#include "presets/Presets.hpp"

#ifndef LEDHANDLER_H
#define LEDHANDLER_H

//Global Vars
extern CRGB leds[LED_COUNT];
extern Preset current_preset;

extern int value;
extern bool should_update_strip;

//Preset Instances
extern Fading f;
extern Rainbow r;
extern RainbowStatic rs;
extern RainbowMoving rm;
extern ComeNGo cng;
extern Blink b;
extern RainbowBlink rb;
extern Custom c;
//extern SongReactive sr;
extern Solid s;
extern Fire fi;

class LED {

public:
    static void setPreset(Preset p, bool fade = true);
    static void setSolid(CHSV color, bool fade = true);
    static void setValue(int v);
    static void loop();
    static void show();
    static Preset str2enum(String str);
};

#endif