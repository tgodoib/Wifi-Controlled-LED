#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <PubSubClient.h>

//Constants
#include <LedConstants.h>

//Handlers
#include <handlers/HomeKit/HomeKitHandler.hpp>
#include <handlers/LedHandler.hpp>
#include <handlers/MqttHandler.hpp>
#include <handlers/OTAHandler.hpp>
#include <handlers/Spotify/SpotifyHandler.cpp>
#include <handlers/Spotify/Track.cpp>
#include <handlers/TimeHandler.hpp>
#include <handlers/WebHandler.hpp>

//Debug
#include <debug/Debug.hpp>

#include "presets/Presets.hpp"

//Static IP Wifi
IPAddress staticIP(192, 168, 1, STATIC_IP);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);
const char *deviceName = "Circulo-do-Tiago-:)";
const char *SSID = "NETGEAR26";
const char *pass = "littleraven971";

void connect_wifi() {

    WiFi.disconnect();

    WiFi.config(staticIP, gateway, subnet, dns);
    WiFi.hostname(deviceName);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, pass);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    LOG::info("Wifi is Connected.");
    LOG::info("IP address: " + WiFi.localIP().toString());
    LOG::info("Gateway: " + WiFi.gatewayIP().toString());
    LOG::info("Subnet Mask: " + WiFi.subnetMask().toString());
    LOG::info("DNS: " + WiFi.dnsIP().toString());
    LOG::line();
}

void setup_fastled() {
    FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, LED_COUNT);
    FastLED.clear();
}

void setup() {
    system_update_cpu_freq(160);

    Serial.begin(115200);

    LOG::start();
    connect_wifi();
    setup_fastled();
    WEB::start();
    MQTT::start();
    OTA::start();
    //TIME::start();
    IOS::start();

    LED::setSolid(CHSV(HSVHue::HUE_GREEN, 255, value));

    //Track tr = spotify.get_song_state();
    //spotify.load_features(tr);
}

void loop() {
    WEB::loop();
    MQTT::loop();

    EVERY_N_MILLIS(16) {
        LED::loop();
    }

    EVERY_N_SECONDS(5) {
        MDNS.announce();
    }

    OTA::loop();
    LOG::loop();
    //TIME::loop();
    IOS::loop();
}
