#include "Arduino.h"
#include "FastLED.h"
#include "LedConstants.h"
#include "Util.cpp"
#include "debug/Debug.hpp"

#ifndef PRESETS_HPP
#define PRESETS_HPP

enum class Preset {
    NONE,
    FADING,
    SOLID,
    RAINBOW,
    RAINBOW_STATIC,
    RAINBOW_MOVING,
    COME_N_GO,
    BLINK,
    RAINBOW_BLINK,
    CUSTOM,
    SPOTIFY,
    FIRE
};

//Externed Vars
extern CRGB leds[LED_COUNT];
extern Preset current_preset;
extern bool should_update_strip;

//Fading
class Fading {

private:
    Preset finalPreset;
    CRGB init[LED_COUNT];
    CRGB final[LED_COUNT];
    int count;

public:
    explicit Fading();
    explicit Fading(Preset p, CRGB *in, CRGB *fi);
    void loop(void show());
};

//Rainbow
class Rainbow {

private:
    int last_hue;

public:
    void loop(void show(), int value);
};

//Rainbow Static
class RainbowStatic {

public:
    bool is_first_run = true;
    void loop(void show(), int value);
};

//Rainbow Moving
class RainbowMoving {

private:
    int step;

public:
    void loop(void show(), int value);
};

//Rainbow Blink
class RainbowBlink {

private:
    int color;

public:
    void loop(void show(), int value);
};

//Come N Go
class ComeNGo {

private:
    int loc = 0;
    bool isGoing = true;

public:
    void loop(void show(), int value);
};

//Blink
class Blink {

private:
    bool isOn = false;

public:
    void loop(void show(), int value);
};

//Custom
extern String custom_preset;
class Custom {

private:
    String raw_preset;
    bool temporizer;
    unsigned int amount;
    std::vector<unsigned int> time;
    std::vector<CRGB> color;

    unsigned int start_time = 0;
    unsigned int current_index = 0;

public:
    explicit Custom(bool t = true);
    void start();
    void loop(void show());
};

//Solid
class Solid {

private:
    CRGB rgb_color;

public:
    CHSV color;

    explicit Solid();
    explicit Solid(CHSV c);
    void loop(void show());
};

//Fire
DECLARE_GRADIENT_PALETTE(fire_gradient);
class Fire {

private:
    CRGBPalette16 firePalette = fire_gradient;
    int y_offset;

public:
    void loop(void show(), float value);
};

#endif