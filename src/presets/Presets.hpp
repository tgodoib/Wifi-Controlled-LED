#include "FastLED.h"
#include "LedConstants.h"
#include "debug/Debug.hpp"
#include "Util.cpp"

#ifndef PRESETS_HPP
#define PRESETS_HPP

enum class PresetType {
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

class Preset {
public:
    PresetType type;

    virtual void start() = 0;
    virtual void loop() = 0;
};

class FadingPreset : public Preset {

private:
    PresetType finalPreset;
    CRGB init[LED_COUNT];
    CRGB final[LED_COUNT];
    int count;

public:
    explicit FadingPreset();
    explicit FadingPreset(PresetType p, CRGB *in, CRGB *fi);
    void start();
    void loop();
};

class RainbowPreset : public Preset {

private:
    int last_hue;
    int last_refresh;

public:
    explicit RainbowPreset();
    void start();
    void loop();
};

class RainbowStaticPreset : public Preset {
public:
    explicit RainbowStaticPreset();
    void start();
    void loop();
};

class RainbowMovingPreset : public Preset {

private:
    int step;
    int last_refresh;

public:
    explicit RainbowMovingPreset();
    void start();
    void loop();
};

class RainbowBlinkPreset : public Preset {

private:
    int color;
    int last_refresh;

public:
    explicit RainbowBlinkPreset();
    void start();
    void loop();
};

class ComeNGoPreset : public Preset {

private:
    int loc;
    bool isGoing;
    int last_refresh;

public:
    explicit ComeNGoPreset();
    void start();
    void loop();
};

class BlinkPreset : public Preset {

private:
    bool isOn;
    int last_refresh;

public:
    explicit BlinkPreset();
    void start();
    void loop();
};

class CustomPreset : public Preset {

private:
    String raw_preset;
    bool temporizer;
    unsigned int amount;
    std::vector<unsigned int> time;
    std::vector<CRGB> color;

    unsigned int start_time = 0;
    unsigned int current_index = 0;

public:
    String custom_preset;
    explicit CustomPreset(bool t = true);
    void start();
    void loop();
};

class SolidPreset : public Preset {

private:
    CHSV solid_color;

public:
    explicit SolidPreset(CHSV c = CHSV(HUE_GREEN, 255, 255));
    void set_color(CHSV c);
    CHSV get_color();
    void start();
    void loop();
};

DECLARE_GRADIENT_PALETTE(fire_gradient);
class FirePreset : public Preset {

private:
    CRGBPalette16 firePalette = fire_gradient;
    int y_offset;

public:
    explicit FirePreset();
    void start();
    void loop();
};

#endif