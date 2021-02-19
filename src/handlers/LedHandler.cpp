#include "LedHandler.hpp"

#ifndef LEDHANDLER_CPP
#define LEDHANDLER_CPP

CRGB LED::leds[LED_COUNT];
Preset *LED::current_preset;
PresetType LED::current_preset_type;

int LED::value = 255;

//Preset
FadingPreset LED::p_fading = FadingPreset();
RainbowPreset LED::p_rainbow = RainbowPreset();
RainbowStaticPreset LED::p_rainbow_static = RainbowStaticPreset();
RainbowMovingPreset LED::p_rainbow_moving = RainbowMovingPreset();
RainbowBlinkPreset LED::p_rainbow_blink = RainbowBlinkPreset();
ComeNGoPreset LED::p_come_n_go = ComeNGoPreset();
BlinkPreset LED::p_blink = BlinkPreset();
CustomPreset LED::p_custom = CustomPreset();
SolidPreset LED::p_solid = SolidPreset();
FirePreset LED::p_fire = FirePreset();

std::map<PresetType, Preset *> LED::preset_list;

bool LED::should_force_loop = false;
bool LED::should_show = true;

void LED::setPreset(PresetType p, bool fade, std::function<void()> config) {
    config();
    current_preset_type = p;
    current_preset = preset_list[p];

    if(fade) {

        CRGB init[LED_COUNT];
        for(int i = 0; i < LED_COUNT; i++) {
            init[i] = leds[i];
        }

        stop_show();
        start_force_loop();
        current_preset->start();
        current_preset->loop();
        start_show();
        stop_force_loop();

        CRGB final[LED_COUNT];
        for(int i = 0; i < LED_COUNT; i++) {
            final[i] = leds[i];
        }

        p_fading = FadingPreset(p, init, final);
        p_fading.start();

    } else {
        update_eeprom();
        current_preset->start();
    }
}

void LED::setValue(int v) {
    value = v;
    setPreset(
        current_preset_type,
        true,
        [&]() { LED::p_solid.set_color(CHSV(p_solid.get_color().h, p_solid.get_color().s, value)); });
}

void LED::start() {

    /* [0] */ preset_list[PresetType::FADING] = &p_fading;
    /* [1] */ preset_list[PresetType::SOLID] = &p_solid;
    /* [2] */ preset_list[PresetType::RAINBOW] = &p_rainbow;
    /* [3] */ preset_list[PresetType::RAINBOW_STATIC] = &p_rainbow_static;
    /* [4] */ preset_list[PresetType::RAINBOW_MOVING] = &p_rainbow_moving;
    /* [5] */ preset_list[PresetType::COME_N_GO] = &p_come_n_go;
    /* [6] */ preset_list[PresetType::BLINK] = &p_blink;
    /* [7] */ preset_list[PresetType::RAINBOW_BLINK] = &p_rainbow_blink;
    /* [8] */ preset_list[PresetType::CUSTOM] = &p_custom;
    /* [9] */ preset_list[PresetType::FIRE] = &p_fire;

    EEPROM.begin(1415);
    bool session_saved = false;
    EEPROM.get(1410, session_saved);
    if(session_saved) {
        LOG::info("Recovered last session from eeprom.");
        LOG::line();

        uint8_t raw_preset = EEPROM.read(1411);
        uint8_t raw_hue = EEPROM.read(1412);
        uint8_t raw_sat = EEPROM.read(1413);
        uint8_t raw_val = EEPROM.read(1414);

        std::map<PresetType, Preset *>::iterator it(preset_list.begin());
        std::advance(it, raw_preset);

        current_preset = it->second;
        current_preset_type = it->first;

        setPreset(PresetType::SOLID, true, [&]() { LED::p_solid.set_color(CHSV(raw_hue, raw_sat, raw_val)); });
    } else {
        LOG::info("Could not recover last session from eeprom.");
        LOG::line();

        current_preset = &p_solid;
        current_preset_type = PresetType::SOLID;

        LOG::debug("Setting Color.");
        setPreset(PresetType::SOLID, true, []() { LED::p_solid.set_color(CHSV(96, 255, 255)); });
    }
    EEPROM.end();
}

void LED::loop() {
    current_preset->loop();
}

void LED::show() {
    if(should_show) {
        FastLED.show();
    }
}

bool LED::get_force_loop() {
    return should_force_loop;
}

void LED::stop_force_loop() {
    should_force_loop = false;
}

void LED::start_force_loop() {
    should_force_loop = true;
}

void LED::stop_show() {
    should_show = false;
}

void LED::start_show() {
    should_show = true;
}

void LED::update_eeprom() {
    // LOG::debug("Updating EEPROM.");
    EEPROM.begin(1415);

    EEPROM.put(1410, true);
    EEPROM.put(1411, uint8_t(std::distance(preset_list.begin(), preset_list.find(current_preset_type))));
    EEPROM.put(1412, uint8_t(p_solid.get_color().h));
    EEPROM.put(1413, uint8_t(p_solid.get_color().s));
    EEPROM.put(1414, uint8_t(LED::value));
    EEPROM.commit();

    bool b = false;
    EEPROM.get(1410, b);
    // LOG::debug(String("[UPDATING] Value at 0x7CF is: ") + String(b));

    EEPROM.end();
}

#endif