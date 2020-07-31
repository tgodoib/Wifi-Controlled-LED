#include <NTPClient.h>
#include <WiFiUdp.h>

#ifndef MQTT_TIME_HANDLER_HPP
#define MQTT_TIME_HANDLER_HPP

extern WiFiUDP ntpUDP;
extern NTPClient timeClient;

class TIME {

public:
    static void start();
    static void loop();
    static int epoch();
};

#endif