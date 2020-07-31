#include "MqttHandler.hpp"

#ifndef MQTT_HANDLER_CPP
#define MQTT_HANDLER_CPP

extern CRGB leds[LED_COUNT];
extern String custom_preset;
extern int value;

//Global Vars
WiFiClient espClient;
PubSubClient mqttClient(espClient);
unsigned long time_start = 0;
unsigned long time_final = 0;

void MQTT::start() {
    mqttClient.setServer("broker.mqtt-dashboard.com", 1883);
    mqttClient.setCallback(MQTT::received);
    LOG::info("MQTT is starting.");
}

void MQTT::received(char *topic, byte *payload, unsigned int length) {
    String msg = "";
    for(unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    LOG::debug("mqtt: " + msg);

    msg = Util::valueFromStr(msg, '.', 0);

    if((char)payload[0] == 'r') { //RGB
        bool fade = (char)payload[1] == 'f';
        if(fade) {
            msg.replace(String((char)payload[1]), "");
        }
        bool keepValue = (char)payload[2] == 'k';
        if(keepValue) {
            msg.replace(String((char)payload[2]), "");
        }

        msg.replace("r", "");
        int r = Util::valueFromStr(msg, ',', 0).toInt();
        int g = Util::valueFromStr(msg, ',', 1).toInt();
        int b = Util::valueFromStr(msg, ',', 2).toInt();

        if(keepValue) {
            r = r * value / 255;
            g = g * value / 255;
            b = b * value / 255;
        }

        LOG::error("Removed support for rgb on solid colors.");
        //LED::setPreset(Preset::SOLID, CRGB(r, g, b), fade);

    } else if((char)payload[0] == 'h') { //HSV
        bool fade = (char)payload[1] == 'f';
        if(fade) {
            msg.replace(String((char)payload[1]), "");
        }
        bool keepValue = (char)payload[2] == 'k';
        if(keepValue) {
            msg.replace(String((char)payload[2]), "");
        }
        msg.replace("h", "");
        int h = Util::valueFromStr(msg, ',', 0).toInt();
        int s = Util::valueFromStr(msg, ',', 1).toInt();
        int v = keepValue ? value : Util::valueFromStr(msg, ',', 2).toInt();
        LED::setSolid(CHSV(h, s, v), fade);

    } else if((char)payload[0] == 'p') { //Preset
        msg.replace("p", "");
        LED::setPreset(LED::str2enum(msg));

    } else if((char)payload[0] == 'v') { //Set Value
        msg.replace("v", "");
        LED::setValue(msg.toInt());

    } else if((char)payload[0] == 't') { //Test Latency
        if((char)payload[1] == 'a') {
            mqttClient.publish("ETRoom-LedStrip", "tb");
            time_start = millis();

        } else if((char)payload[1] == 'b') {
            time_final = millis();
            unsigned long delta = time_final - time_start;
            mqttClient.publish("ETRoom-LedStrip", (char *)String(delta).c_str());
            LED::setSolid(CHSV(0, 255, 100));
        }
    } else if((char)payload[0] == 'c') { //Custom Presets
        msg.replace("c", "");
        custom_preset = String(msg);
        LED::setPreset(Preset::CUSTOM);
    }
}

void MQTT::loop() {
    if(!mqttClient.connected()) {
        reconnect_mqtt();
    }
    mqttClient.loop();
}

void MQTT::publish(String s) {
    mqttClient.publish("ETRoom-LedStrip", (char *)String(s).c_str());
}

void MQTT::reconnect_mqtt() {
    LOG::info("Attempting MQTT connection...");
    String clientId = "ETRoom-";
    clientId += String(random(0xffff), HEX);

    if(mqttClient.connect(clientId.c_str())) {
        LOG::info("connected");
        LOG::line();
        mqttClient.subscribe("ETRoom-LedStrip");

    } else {
        LOG::error("failed, rc=" + String(mqttClient.state()));
        LOG::error(" try again in 5 seconds");
        delay(5000);
    }
}

#endif