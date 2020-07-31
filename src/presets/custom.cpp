#include "Presets.hpp"

#ifndef CUSTOM_CPP
#define CUSTOM_CPP

//Global Vars
String custom_preset;

extern CRGB leds[LED_COUNT];

Custom::Custom(bool t) {
    raw_preset = custom_preset;
    temporizer = t;
}

void Custom::start() {

    String preset = !temporizer ? raw_preset : String("c1;0-0,0,0;200-255,255,255;1000-0,0,0;1200-255,255,255;2000-0,0,0;2200-255,255,255;3000-0,0,0;");

    amount = Util::valueFromStr(preset, ';', 0).toInt();

    for(unsigned int i = 0; i < amount; i++) {
        time.push_back(Util::valueFromStr(Util::valueFromStr(preset, ';', i + 1), '-', 0).toInt());
        String raw_color = Util::valueFromStr(Util::valueFromStr(preset, ';', i + 1), '-', 1);
        raw_color.replace(";", "");
        color.push_back(CRGB(
            Util::valueFromStr(raw_color, ',', 0).toInt(),
            Util::valueFromStr(raw_color, ',', 1).toInt(),
            Util::valueFromStr(raw_color, ',', 2).toInt()));
    }

    delay(200);
    start_time = millis();
}

void Custom::loop(void show()) {
    unsigned long delay = millis() - start_time;
    if(amount > current_index) {
        if(delay >= time[current_index]) {
            LOG::debug(String(current_index) + String(". Delay: ") + String(delay));
            time[current_index + 1] -= delay - time[current_index];
            for(int i = 0; i < LED_COUNT; i++) {
                leds[i] = color[current_index];
            }

            show();

            current_index++;
        }
    } else if(temporizer) {
        temporizer = !temporizer;
        start();
    }
}

#endif