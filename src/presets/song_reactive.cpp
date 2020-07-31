#include "Arduino.h"
#include "FastLED.h"
#include <LedConstants.h>
#include "handlers/Spotify/Track.cpp"
#include "ArduinoJson.hpp"

#ifndef SONG_REACTIVE_CPP
#define SONG_REACTIVE_CPP

class SongReactive {

private:
    Track track;

public:

    void set_track(Track t){
        track = t;
    }

    CRGB *update(int value) {
        track.update();

        CRGB temp[LED_COUNT];
        return temp;
    }
};

#endif