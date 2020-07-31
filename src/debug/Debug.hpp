#include "PrintType.cpp"
#include "WString.h"
#include "ESP8266WiFi.h"

#ifndef DEBUG_H
#define DEBUG_H

extern WiFiServer telnetServer;
extern WiFiClient telnetClient;
extern unsigned int startTime;
extern std::pair<PrintType, String> printLine[64];

class LOG {

public:
    static void start();
    static void loop();

    static bool line(bool isRetrying = false);
    static bool info(String s, bool isRetrying = false);
    static bool debug(String s, bool isRetrying = false);
    static bool error(String s, bool isRetrying = false);

private:
    static bool sendMsg(String msg, PrintType type, String prefix, String colorCode, bool retrying);
};

#endif