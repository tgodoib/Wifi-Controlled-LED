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
            "<html><head> <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/gh/bebraw/colorjoe/css/colorjoe.css\"> <script src=\"https://cdn.jsdelivr.net/gh/bebraw/colorjoe/dist/colorjoe.min.js\"></script> <script src=\"https://code.jquery.com/jquery-3.4.1.min.js\"></script> <style> * { margin: 0; padding: 0; } .colorPicker { margin: 0; width: 98%; border: 0px; background-color: white; border-radius: 0 0 5% 5%; padding: 10px; } .colorPicker .twod, .colorPicker .twod .bg { width: 75%; height: 40%; border: 0px; border-radius: 0 0 0 5%; } .colorPicker .twod .bg2 { width: 73.5%; } .colorPicker .oned { width: 21%; height: 40%; } .colorPicker .oned .bg { width: 100%; height: 100%; border: 0px; border-radius: 0 0 20px 0; } .colorPicker .oned .pointer .shape { width: 101%; height: 15px; background-color: white; border: 0px; } #presets { width: 100%; height: 50%; overflow-y: scroll; font-size: 80px; text-align: center; font-family: DejaVu Sans Mono, monospace; font-weight: bold; margin-top: 100px; } #presets a { display: block; margin: 20px; padding: 10px; color: black; text-decoration: none; background-color: rgba(255, 255, 255, 0.5); border-radius: 50px; } </style></head><body> <div id=\"picker\" class=\"colorPicker\"></div> <div id=\"presets\"> <a href=\"?p=RAINBOW\">Rainbow</a> <a href=\"?p=RAINBOW_STATIC\">Rainbow Static</a> <a href=\"?p=RAINBOW_MOVING\">Rainbow Moving</a> <a href=\"?p=COME_N_GO\">Come N Go</a> <a href=\"?p=BLINK\">Blink</a> </div> <script> const joe = colorjoe.rgb(\'picker\', \"rgb(\" + getUrlVars()[\"rgb\"] + \")\", []); joe.on(\"change\", function (color) { $(\"body\").css(\"background-color\", color.css()); }); joe.on(\"done\", function (color) { window.location.href = \"?rgb=\" + color.css().replace(/ /g, \"\").replace(\"rgb(\", \"\").replace(\")\", \"\"); }); function getUrlVars() { var vars = {}; var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function (m, key, value) { vars[key] = value; }); return vars; } function getWidth() { return Math.min( document.body.scrollWidth, document.documentElement.scrollWidth, document.body.offsetWidth, document.documentElement.offsetWidth, document.documentElement.clientWidth ); } $(\"body\").css(\"background-color\", \"rgb(\" + getUrlVars()[\"rgb\"] + \")\"); </script></body></html>";
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