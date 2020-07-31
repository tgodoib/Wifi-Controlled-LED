#include "OTAHandler.hpp"

#ifndef OTAHANDLER_CPP
#define OTAHANDLER_CPP

void OTA::start() {
    ArduinoOTA.onStart([]() {
        String type;
        if(ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {
            type = "filesystem";
        }

        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        LOG::info("Start updating " + type);
    });

    ArduinoOTA.onEnd([]() {
        LOG::info("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        LOG::debug("Progress: " + String(progress / (total / 100)) + "\r");
    });

    ArduinoOTA.onError([](ota_error_t error) {
        LOG::error("Error: ");
        if(error == OTA_AUTH_ERROR) {
            LOG::error("Auth Failed");
        } else if(error == OTA_BEGIN_ERROR) {
            LOG::error("Begin Failed");
        } else if(error == OTA_CONNECT_ERROR) {
            LOG::error("Connect Failed");
        } else if(error == OTA_RECEIVE_ERROR) {
            LOG::error("Receive Failed");
        } else if(error == OTA_END_ERROR) {
            LOG::error("End Failed");
        }
    });

    ArduinoOTA.begin();
}

void OTA::loop() {
    ArduinoOTA.handle();
}

#endif