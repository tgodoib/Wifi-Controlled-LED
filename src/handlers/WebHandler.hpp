#include "Arduino.h"
#include "FastLED.h"
#include "Util.cpp"
#include "handlers/LedHandler.hpp"
#include "handlers/Spotify/SpotifyHandler.cpp"
#include "presets/Presets.hpp"
#include <ESP8266WebServer.h>

#ifndef WEBHANDLER_HPP
#define WEBHANDLER_HPP

extern ESP8266WebServer webServer;

class WEB {

public:
    static void start();
    static void received();
    static void callback();
    static void loop();
};

#endif