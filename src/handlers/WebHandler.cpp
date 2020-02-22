#include "Arduino.h"
#include "FastLED.h"
#include "Util.cpp"
#include "handlers/LedHandler.cpp"
#include "presets/Preset.cpp"
#include <ESP8266WebServer.h>

#ifndef WEBHANDLER_CPP
#define WEBHANDLER_CPP

extern ESP8266WebServer webServer;
extern int value;

class WEB {

public:
    static void start() {
        webServer.on("/", WEB::received);
        webServer.begin();
    }

    static void received() {
        String message =
            "<html><head> <title>Led Color</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <link rel=\"stylesheet\" href=\"https://meyerweb.com/eric/tools/css/reset/reset.css\"> <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/style.css\"> <script src=\"https://cdn.jsdelivr.net/gh/bebraw/colorjoe/dist/colorjoe.min.js\"></script> <script src=\"https://code.jquery.com/jquery-3.4.1.min.js\"></script></head><body> <div class=\"block\"> <div id=\"picker\"></div> </div> <div id=\"presets\" class=\"block\"> <p>Presets</p> <div id=\"preset-box\"> <a href=\"?rgb=0,0,0\">Turn Off</a> <a href=\"?p=RAINBOW\">Rainbow</a> <a href=\"?p=RAINBOW_STATIC\">Rainbow Static</a> <a href=\"?p=RAINBOW_MOVING\">Rainbow Moving</a> <a href=\"?p=COME_N_GO\">Come N Go</a> <a href=\"?p=BLINK\">Blink</a> </div> </div> <script src=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/script.js\"></script></body></html>";
        if (webServer.arg("v") != "") {
            value = webServer.arg("i").toInt();
        }

        //float i_percent = float(value) / 255;

        if (webServer.arg("p") != "") {
            LED::setPreset(LED::str2enum(webServer.arg("p")));
        } else if (webServer.arg("rgb") != "") {
            String rgb = webServer.arg("rgb");
            int r = Util::valueFromStr(rgb, ',', 0).toInt();
            int g = Util::valueFromStr(rgb, ',', 1).toInt();
            int b = Util::valueFromStr(rgb, ',', 2).toInt();
            LED::setPreset(Preset::SOLID, CRGB(r, g, b));
        }

        webServer.send(200, "text/html", message);
    }

    static void loop() {
        webServer.handleClient();
    }
};

#endif