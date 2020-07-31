#include "Arduino.h"
#include "FastLED.h"
#include "PubSubClient.h"
#include "Util.cpp"
#include "LedHandler.hpp"
#include "debug/Debug.hpp"
#include "handlers/TimeHandler.hpp"
#include "presets/Presets.hpp"
#include <LedConstants.h>

#ifndef MQTT_HANDLER_HPP
#define MQTT_HANDLER_HPP

extern WiFiClient espClient;
extern PubSubClient mqttClient;
extern unsigned long time_start;
extern unsigned long time_final;

class MQTT {

public:
    static void start();
    static void received(char *topic, byte *payload, unsigned int length);
    static void loop();
    static void publish(String s);
    static void reconnect_mqtt();
};

#endif