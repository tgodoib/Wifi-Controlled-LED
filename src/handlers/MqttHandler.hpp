#include "Arduino.h"
#include "FastLED.h"
#include "PubSubClient.h"

#include "LedHandler.hpp"
#include "Util.cpp"
#include "auth/secrets.hpp"
#include "debug/Debug.hpp"

#include "presets/Presets.hpp"
#include <LedConstants.h>

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <time.h>

#ifndef MQTT_HANDLER_HPP
#define MQTT_HANDLER_HPP

// extern WiFiClient espClient;
extern WiFiClientSecure espClient;
extern PubSubClient mqttClient;
// extern unsigned long time_start;
// extern unsigned long time_final;
extern time_t now;
extern time_t nowish;

class MQTT {

public:
    static void start();
    static void loop();
    static void received(char *topic, byte *payload, unsigned int length);
    static void publish(String s);

    static String error_code(int8_t MQTTErr);
    static void reconnect_mqtt();

private:
    static int reconnect_tries;
    static void setup_ntp();
    static int last_reconnect_time;
};

#endif

/* 
{
    "color": [255, 255, 255],
    "fade": true,
    "keep_value": true
}

{
    "preset": "BLINK"
}

{
    "value": 0
}

 */