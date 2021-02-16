#include "LedHandler.hpp"

#ifndef LEDHANDLER_CPP
#define LEDHANDLER_CPP

//Global Vars
CRGB leds[LED_COUNT];
Preset current_preset;

int value = 255;
bool should_update_strip;

//Preset Instances
Fading f = Fading();
Rainbow r = Rainbow();
RainbowStatic rs = RainbowStatic();
RainbowMoving rm = RainbowMoving();
RainbowBlink rb = RainbowBlink();
ComeNGo cng = ComeNGo();
Blink b = Blink();
Custom c = Custom();
//SongReactive sr = SongReactive();
Solid s;
Fire fi = Fire();

void LED::setPreset(Preset p, bool fade) {
    current_preset = p;
    should_update_strip = true;

    if(p == Preset::CUSTOM) {
        c = Custom();
        c.start();
    } /* else if(p == Preset::SPOTIFY) {
            t = spotify.get_song_state();
            spotify.load_features(t);
            sr.set_track(t);
        } */
    else {
        if(fade) {
            CRGB init[LED_COUNT];
            for(int i = 0; i < LED_COUNT; i++) {
                init[i] = leds[i];
            }
            should_update_strip = false;
            loop();
            CRGB final[LED_COUNT];
            for(int i = 0; i < LED_COUNT; i++) {
                final[i] = leds[i];
            }
            should_update_strip = true;
            f = Fading(p, init, final);
        } else {
            FastLED.show();
        }
    }
}

void LED::setSolid(CHSV color, bool fade) {
    s = Solid(color);
    setPreset(Preset::SOLID, fade);
}

void LED::setValue(int v) {
    value = v;
    if(current_preset == Preset::SOLID) {
        setSolid(CHSV(s.color.h, s.color.s, v));
    } else if(current_preset == Preset::RAINBOW_STATIC) {
        setPreset(Preset::RAINBOW_STATIC);
    }
}

void LED::loop() {
    if(current_preset == Preset::NONE) {
        Solid s = Solid(CHSV(0, 0, 0));
        s.loop(LED::show);
    } else if(current_preset == Preset::FADING) {
        f.loop(LED::show);
    } else if(current_preset == Preset::SOLID) {
        s.loop(LED::show);
    } else if(current_preset == Preset::RAINBOW) {
        r.loop(LED::show, value);
    } else if(current_preset == Preset::RAINBOW_STATIC) {
        rs.loop(LED::show, value);
    } else if(current_preset == Preset::RAINBOW_MOVING) {
        rm.loop(LED::show, value);
    } else if(current_preset == Preset::COME_N_GO) {
        cng.loop(LED::show, value);
    } else if(current_preset == Preset::BLINK) {
        b.loop(LED::show, value);
    } else if(current_preset == Preset::RAINBOW_BLINK) {
        rb.loop(LED::show, value);
    } else if(current_preset == Preset::CUSTOM) {
        c.loop(LED::show);
    } else if(current_preset == Preset::SPOTIFY) {
        //*leds = *sr.update(value);
    } else if(current_preset == Preset::FIRE) {
        fi.loop(LED::show, value);
    }
}

void LED::show() {
    if(should_update_strip) {
        FastLED.show();
    }
}

Preset LED::str2enum(String str) {
    if(str == "SOLID") {
        return Preset::SOLID;
    } else if(str == "RAINBOW") {
        return Preset::RAINBOW;
    } else if(str == "RAINBOW_STATIC") {
        return Preset::RAINBOW_STATIC;
    } else if(str == "RAINBOW_MOVING") {
        return Preset::RAINBOW_MOVING;
    } else if(str == "COME_N_GO") {
        return Preset::COME_N_GO;
    } else if(str == "BLINK") {
        return Preset::BLINK;
    } else if(str == "RAINBOW_BLINK") {
        return Preset::RAINBOW_BLINK;
    } else if(str == "SPOTIFY") {
        return Preset::SPOTIFY;
    } else if(str == "FIRE") {
        return Preset::FIRE;
    }

    return Preset::NONE;
}

#endif