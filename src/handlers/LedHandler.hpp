#include "Arduino.h"
#include "FastLED.h"
#include <functional>
#include <string>
#include <map>
#include <EEPROM.h>

//Presets
#include "presets/Presets.hpp"

#ifndef LEDHANDLER_H
#define LEDHANDLER_H

class LED {

public:
    static CRGB leds[LED_COUNT];
    static Preset *current_preset;
    static PresetType current_preset_type;

    static int value;

    //Preset
    static FadingPreset p_fading;
    static RainbowPreset p_rainbow;
    static RainbowStaticPreset p_rainbow_static;
    static RainbowMovingPreset p_rainbow_moving;
    static ComeNGoPreset p_come_n_go;
    static BlinkPreset p_blink;
    static RainbowBlinkPreset p_rainbow_blink;
    static CustomPreset p_custom;
    static SolidPreset p_solid;
    static FirePreset p_fire;

    static std::map<PresetType, Preset *> preset_list;

    static void setPreset(PresetType p, bool fade = true, std::function<void()> config = []() {});
    static void setValue(int v);

    static void start();
    static void loop();
    static void show();

    static bool get_force_loop();

    static void stop_show();
    static void start_show(); 

    static void update_eeprom(); 

    private:
        static bool should_force_loop;
        static bool should_show;

        static void stop_force_loop();
        static void start_force_loop();  
};

// namespace std {
//     template <>
//     struct hash<PresetType> {
//         typedef PresetType argument_type;
//         typedef size_t result_type;

//         result_type operator()(const argument_type &x) const {
//             using type = typename std::underlying_type<argument_type>::type;
//             return std::hash<type>()(static_cast<type>(x));
//         }
//     };
// } // namespace std

#endif