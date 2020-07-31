#include "TimeHandler.hpp"

#ifndef MQTT_TIME_HANDLER_CPP
#define MQTT_TIME_HANDLER_CPP

//Global Vars
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 60 * 60);

void TIME::start() {
    timeClient.begin();
}

void TIME::loop() {
    timeClient.update();
}

int TIME::epoch() {
    return (int)timeClient.getEpochTime();
}

#endif