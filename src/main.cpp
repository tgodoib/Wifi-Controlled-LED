#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <PubSubClient.h>

#define DATA_PIN 6
#define NUM_LEDS 56

//Presets
#include <presets/Preset.cpp>
#include <presets/blink.cpp>
#include <presets/comeNgo.cpp>
#include <presets/rainbow.cpp>
#include <presets/rainbow_moving.cpp>
#include <presets/rainbow_static.cpp>
#include <presets/solid.cpp>
#include <presets/Fading.cpp>

//Preset Instances
Fading f = Fading();
Rainbow r = Rainbow();
RainbowStatic rs = RainbowStatic();
RainbowMoving rm = RainbowMoving();
ComeNGo cng = ComeNGo();
Blink b = Blink();

//Handlers
#include <handlers/LedHandler.cpp>
#include <handlers/MqttHandler.cpp>
#include <handlers/WebHandler.cpp>

//Led Handler
int value = 255;
CRGB leds[56];
Preset current_preset;
CRGB solid_color;

//MQTT Handler
WiFiClient espClient;
PubSubClient mqttClient(espClient);

//Web Handler
ESP8266WebServer webServer(80);

//Static IP Wifi
IPAddress staticIP(192, 168, 1, 6);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);
const char *deviceName = "Led-do-Tiago-:)";
const char *SSID = "NETGEAR26";
const char *pass = "littleraven971";

void connect_wifi() {
    WiFi.disconnect();

    WiFi.config(staticIP, subnet, gateway, dns);
    WiFi.hostname(deviceName);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Wifi is Connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void connect_mqtt() {
    mqttClient.setServer("broker.mqtt-dashboard.com", 1883);
    mqttClient.setCallback(MQTT::received);
    Serial.println("MQTT is starting.");
}

void start_webServer() {
    WEB::start();
    Serial.println("Web Server listening.");
}

void setup_fastled() {
    FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
    FastLED.clear();
}

void setup() {
    Serial.begin(115200);

    connect_wifi();
    setup_fastled();
    start_webServer();
    connect_mqtt();

    //LED::setPreset(Preset::SOLID, CRGB(0, 255, 0));
    current_preset = Preset::SOLID;
    solid_color = CRGB(0, 255, 0);
}

void loop() {
    WEB::loop();
    MQTT::loop();
    LED::loop();
}
