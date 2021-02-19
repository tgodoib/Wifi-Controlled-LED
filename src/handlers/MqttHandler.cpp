#include "MqttHandler.hpp"

const char MQTT_SUB_TOPIC[] = "$aws/things/RoomLED/shadow/update";
const char MQTT_PUB_TOPIC[] = "$aws/things/RoomLED/shadow/update";

WiFiClientSecure espClient;
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient mqttClient(espClient);

time_t now;
time_t nowish = 1510592825;

int MQTT::reconnect_tries = 0;
int MQTT::last_reconnect_time = 0;

void MQTT::start() {
    MQTT::setup_ntp();
    espClient.setTrustAnchors(&cert);
    espClient.setClientRSACert(&client_crt, &key);
    mqttClient.setServer(MQTT_HOST, 8883);
    mqttClient.setCallback(MQTT::received);
    reconnect_mqtt();
}

void MQTT::loop() {
    if(!mqttClient.connected() && millis() - last_reconnect_time >= 6000) {
        reconnect_mqtt();
    }
    mqttClient.loop();
}

void MQTT::received(char *topic, byte *payload, unsigned int length) {
    if(String(topic).equals("HSV")) {
        StaticJsonDocument<96> doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if(error) {
            LOG::error(String("MQTT: deserializeJson() failed -> ") + String(error.f_str()));
            return;
        }

        bool fade = doc["fade"];
        bool keep_value = doc["keep_value"];

        JsonArray color = doc["color"];
        int h = color[0];
        int s = color[1];
        int v = keep_value ? LED::value : color[2];

        // [=] or [&]
        LED::setPreset(PresetType::SOLID, fade, [&]() { LED::p_solid.set_color(CHSV(h, s, v)); });

    } else if(String(topic).equals("Preset")) {
        StaticJsonDocument<16> doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if(error) {
            LOG::error(String("MQTT: deserializeJson() failed -> ") + String(error.f_str()));
            return;
        }

        const char *preset = doc["preset"];

        std::map<PresetType, Preset *>::iterator it(LED::preset_list.begin());
        std::advance(it, String(preset).toInt());
        LED::setPreset(it->first);

    } else if(String(topic).equals("Value")) {
        StaticJsonDocument<16> doc;
        DeserializationError error = deserializeJson(doc, payload, length);

        if(error) {
            LOG::error(String("MQTT: deserializeJson() failed -> ") + String(error.f_str()));
            return;
        }

        int value = doc["value"];

        LED::setValue(value);
    }
}

void MQTT::publish(String s) {
    DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
    JsonObject root = jsonBuffer.to<JsonObject>();
    JsonObject state = root.createNestedObject("state");
    JsonObject state_reported = state.createNestedObject("reported");
    state_reported["value"] = random(100);
    Serial.printf("Sending  [%s]: ", MQTT_PUB_TOPIC);
    serializeJson(root, Serial);
    Serial.println();
    char shadow[measureJson(root) + 1];
    serializeJson(root, shadow, sizeof(shadow));
    if(!mqttClient.publish(MQTT_PUB_TOPIC, shadow, false)) {
        LOG::error(String("MQTT: ") + MQTT::error_code(mqttClient.state()));
    }
    // mqttClient.publish(MQTT_PUB_TOPIC, (char *)String(s).c_str());
}

String MQTT::error_code(int8_t MQTTErr) {
    if(MQTTErr == MQTT_CONNECTION_TIMEOUT)
        return "Connection tiemout";
    else if(MQTTErr == MQTT_CONNECTION_LOST)
        return "Connection lost";
    else if(MQTTErr == MQTT_CONNECT_FAILED)
        return "Connect failed";
    else if(MQTTErr == MQTT_DISCONNECTED)
        return "Disconnected";
    else if(MQTTErr == MQTT_CONNECTED)
        return "Connected";
    else if(MQTTErr == MQTT_CONNECT_BAD_PROTOCOL)
        return "Connect bad protocol";
    else if(MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID)
        return "Connect bad Client-ID";
    else if(MQTTErr == MQTT_CONNECT_UNAVAILABLE)
        return "Connect unavailable";
    else if(MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS)
        return "Connect bad credentials";
    else if(MQTTErr == MQTT_CONNECT_UNAUTHORIZED)
        return "Connect unauthorized";

    return "Unknown Error";
}

void MQTT::reconnect_mqtt() {
    LOG::info("Attempting MQTT connection...");

    if(mqttClient.connect("RoomLED")) {
        LOG::info("MQTT: Connected.");
        LOG::line();
        if(!mqttClient.subscribe("RGB")) {
            LOG::error(String("MQTT: Error subscribing to ") + String("RGB") + MQTT::error_code(mqttClient.state()));
        }
        if(!mqttClient.subscribe("HSV")) {
            LOG::error(String("MQTT: Error subscribing to ") + String("HSV") + MQTT::error_code(mqttClient.state()));
        }
        if(!mqttClient.subscribe("Preset")) {
            LOG::error(String("MQTT: Error subscribing to ") + String("Preset") + MQTT::error_code(mqttClient.state()));
        }
        if(!mqttClient.subscribe("Value")) {
            LOG::error(String("MQTT: Error subscribing to ") + String("Value") + MQTT::error_code(mqttClient.state()));
        }

    } else {
        reconnect_tries++;
        if(reconnect_tries >= 10) {
            LOG::error("Tried too many times. Reseting LED.");
            wdt_disable();
            wdt_enable(WDTO_15MS);
            while(1) {}
        } else {
            LOG::error(String("MQTT: ") + MQTT::error_code(mqttClient.state()));
            LOG::error("Trying again in 5 seconds");
            last_reconnect_time = millis();
        }
    }
}

void MQTT::setup_ntp() {
    LOG::info("MQTT: Setting up MQTT time");

    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);

    while(now < nowish) {
        delay(500);
        // Serial.print(".");
        now = time(nullptr);
    }

    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    // LOG::line();
    LOG::info(String("MQTT: Current Time -> ") + String(asctime(&timeinfo)));
}