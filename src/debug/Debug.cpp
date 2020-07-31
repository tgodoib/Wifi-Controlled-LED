#include "Debug.hpp"
#include "Arduino.h"
#include "ESP8266WiFi.h"

#ifndef DEBUG_CPP
#define DEBUG_CPP

//Global Vars
WiFiServer telnetServer(23);
WiFiClient telnetClient;
unsigned int startTime;
std::pair<PrintType, String> printLine[64];

void LOG::start() {

    telnetServer.begin();
    telnetServer.setNoDelay(true);
    startTime = millis();

    for(int i = 0; i < 64; i++) {
        printLine[i] = std::pair<PrintType, String>(PrintType::NONE, "");
    }
}

void LOG::loop() {
    if(telnetServer.hasClient()) {
        if(!telnetClient || !telnetClient.connected()) {
            if(telnetClient) {
                telnetClient.stop();
                LOG::debug("Telnet Client Stop");
            }
            telnetClient = telnetServer.available();
            LOG::debug("New Telnet client");
            telnetClient.flush();
        }
    }

    while(telnetClient.available()) { // get data from Client
        Serial.write(telnetClient.read());
    }

    if(millis() - startTime > 3000) {
        //startTime = millis();
        for(int i = 0; i < 64; i++) {
            std::pair<PrintType, String> item = printLine[i];
            if(item.first == PrintType::INFO) {
                if(LOG::info(item.second, true))
                    printLine[i] = std::pair<PrintType, String>(PrintType::NONE, "");
            } else if(item.first == PrintType::DEBUG) {
                if(LOG::debug(item.second, true))
                    printLine[i] = std::pair<PrintType, String>(PrintType::NONE, "");
            } else if(item.first == PrintType::ERROR) {
                if(LOG::error(item.second, true))
                    printLine[i] = std::pair<PrintType, String>(PrintType::NONE, "");
            } else if(item.first == PrintType::SPACE) {
                if(LOG::line(true))
                    printLine[i] = std::pair<PrintType, String>(PrintType::NONE, "");
            }
        }
    }
}

bool LOG::line(bool isRetrying) {
    return sendMsg("", PrintType::SPACE, "", "", isRetrying);
}

bool LOG::info(String s, bool isRetrying) {
    return sendMsg(s, PrintType::INFO, "[INFO]", "\u001b[36m", isRetrying);
}

bool LOG::debug(String s, bool isRetrying) {
    return sendMsg(s, PrintType::DEBUG, "[DEBUG]", "\u001b[33m", isRetrying);
}

bool LOG::error(String s, bool isRetrying) {
    return sendMsg(s, PrintType::ERROR, "[ERROR]", "\u001b[31m", isRetrying);
}

bool LOG::sendMsg(String msg, PrintType type, String prefix, String colorCode, bool retrying) {
    if(millis() - startTime > 2000) {
        if(telnetClient && telnetClient.connected()) { // send data to Client
            telnetClient.println(colorCode + prefix + msg + "\u001b[0m");
            Serial.println(prefix + msg);
            return true;
        }
    }
    if(!retrying) {
        Serial.println(prefix + msg);
        for(int i = 0; i < 64; i++) {
            if(printLine[i].first == PrintType::NONE) {
                printLine[i] = std::pair<PrintType, String>(type, msg);
                break;
            }
        }
    }
    return false;
}

#endif
