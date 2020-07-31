#include "Arduino.h"
#include "debug/Debug.hpp"
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#ifndef OTAHANDLER_HPP
#define OTAHANDLER_HPP

class OTA {

public:
    static void start();
    static void loop();
};

#endif