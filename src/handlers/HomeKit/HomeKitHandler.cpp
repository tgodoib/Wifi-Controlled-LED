#include "HomeKitHandler.hpp"
#include "FastLED.h"
#include "../LedHandler.hpp"
#include "presets/Presets.hpp"
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <debug/Debug.hpp>

#ifndef HOME_KIT_HANDLER_CPP
#define HOME_KIT_HANDLER_CPP

extern "C" homekit_server_config_t accessory_config;

extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_sat;
extern "C" homekit_characteristic_t cha_hue;

// extern Preset current_preset;
// extern Solid s;
// extern int value;

void IOS::start() {
    //homekit_storage_reset();

    t_report = millis();
    t_heap = millis();

    cha_on.setter = IOS::set_on;
    cha_bright.setter = IOS::set_bright;
    cha_sat.setter = IOS::set_sat;
    cha_hue.setter = IOS::set_hue;

    arduino_homekit_setup(&accessory_config);

    LOG::info("IOS: Ready.");
    LOG::line();
}

void IOS::loop() {
    arduino_homekit_loop();

    const uint32_t t = millis();
    if(t > t_report) {
        t_report = t + 10 * 1000;
        report();
    }
    if(t > t_heap) {
        t_heap = t + 5 * 1000;
        Serial.printf("Free heap: %d, HomeKit clients: %d \n", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
    }
}

void IOS::report() {
    cha_on.value.bool_value = LED::value > 0;
    homekit_characteristic_notify(&cha_on, cha_on.value);

    cha_hue.value.float_value = (float)LED::p_solid.get_color().hue / 255.0 * 360.0;
    homekit_characteristic_notify(&cha_hue, cha_hue.value);

    cha_bright.value.int_value = (int)round(LED::value / 255.0 * 100.0);
    homekit_characteristic_notify(&cha_bright, cha_bright.value);

    cha_sat.value.float_value = (float)LED::p_solid.get_color().sat / 255.0 * 100.0;
    homekit_characteristic_notify(&cha_sat, cha_sat.value);
}

void IOS::set_on(const homekit_value_t v) {
    bool on = v.bool_value;
    cha_on.value.bool_value = on; //sync the value

    if(on && LED::value == 0) {
        LED::setValue(255);
    } else if(!on) {
        LOG::debug(String(LED::p_solid.get_color().h));
        LOG::debug(String(LED::p_solid.get_color().s));
        LOG::debug(String(LED::p_solid.get_color().v));
        LED::setValue(0);
    }
}

void IOS::set_hue(const homekit_value_t v) {
    float hue = v.float_value;
    cha_hue.value.float_value = hue; //sync the value

    if((incomplete_color.is_hue_set && !incomplete_color.is_sat_set) || (!incomplete_color.is_hue_set && !incomplete_color.is_sat_set)) {
        incomplete_color = IOS::FullColor();
        incomplete_color.hue = (hue / 360.0) * 255.0;
        incomplete_color.is_hue_set = true;
    } else if(!incomplete_color.is_hue_set && incomplete_color.is_sat_set) {
        if(LED::value == 0) { LED::setValue(255); }
        LED::setPreset(PresetType::SOLID, true, [&]() { LED::p_solid.set_color(CHSV((hue / 360.0) * 255.0, incomplete_color.sat, LED::value)); });
        incomplete_color = IOS::FullColor();
    }
}

void IOS::set_sat(const homekit_value_t v) {
    float sat = v.float_value;
    cha_sat.value.float_value = sat; //sync the value

    if((!incomplete_color.is_hue_set && incomplete_color.is_sat_set) || (!incomplete_color.is_hue_set && !incomplete_color.is_sat_set)) {
        incomplete_color = IOS::FullColor();
        incomplete_color.sat = (sat / 100.0) * 255.0;
        incomplete_color.is_sat_set = true;
    } else if(incomplete_color.is_hue_set && !incomplete_color.is_sat_set) {
        if(LED::value == 0) { LED::setValue(255); }
        LED::setPreset(PresetType::SOLID, true, [&]() { LED::p_solid.set_color(CHSV(incomplete_color.hue, (sat / 100.0) * 255.0, LED::value)); });
        incomplete_color = IOS::FullColor();
    }
}

void IOS::set_bright(const homekit_value_t v) {
    int bright = v.int_value;
    cha_bright.value.int_value = bright; //sync the value
    LED::setValue((bright / 100.0) * 255.0);
}

#endif