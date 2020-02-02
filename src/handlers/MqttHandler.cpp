#include "Arduino.h"
#include "FastLED.h"
#include "PubSubClient.h"
#include "Util.cpp"
#include "handlers/LedHandler.cpp"
#include "presets/Preset.cpp"

extern CRGB leds[56];
extern PubSubClient mqttClient;
extern int value;

class MQTT {

public:
    static void received(char *topic, byte *payload, unsigned int length) {
        String msg = "";
        for (unsigned int i = 0; i < length; i++) {
            msg += (char)payload[i];
        }
        Serial.println("mqtt: " + msg);

        if ((char)payload[0] == 'r') {
            msg.replace("r", "");
            int r = Util::valueFromStr(msg, ',', 0).toInt();
            int g = Util::valueFromStr(msg, ',', 1).toInt();
            int b = Util::valueFromStr(msg, ',', 2).toInt();

            LED::setPreset(Preset::SOLID, CRGB(r, g, b));
        } else if ((char)payload[0] == 'h') {
            msg.replace("h", "");
            int h = Util::valueFromStr(msg, ',', 0).toInt();
            int s = Util::valueFromStr(msg, ',', 1).toInt();
            int v = Util::valueFromStr(msg, ',', 2).toInt();

            LED::setPreset(Preset::SOLID, CHSV(h, s, v));
        } else if ((char)payload[0] == '?') {
            msg.replace("?", "");
            LED::setPreset(LED::str2enum(msg));
        } else if ((char)payload[0] == 'v') {
            msg.replace("v", "");
            value = msg.toInt();
        }
    }

    static void loop() {
        if (!mqttClient.connected()) {
            reconnect_mqtt();
        }
        mqttClient.loop();
    }

    static void reconnect_mqtt() {
        while (!mqttClient.connected()) {
            Serial.print("Attempting MQTT connection...");
            String clientId = "ETRoom-";
            clientId += String(random(0xffff), HEX);

            if (mqttClient.connect(clientId.c_str())) {
                Serial.println("connected");
                mqttClient.subscribe("ETRoom-LedStrip");

            } else {
                Serial.print("failed, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" try again in 5 seconds");
                delay(5000);
            }
        }
    }
};