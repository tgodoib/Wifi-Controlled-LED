#include "WebHandler.hpp"

#ifndef WEBHANDLER_CPP
#define WEBHANDLER_CPP

extern int value;
//extern Spotify spotify;

//Global Vars
ESP8266WebServer webServer(80);

void WEB::start() {
    webServer.on("/", WEB::received);
    webServer.on("/callback", WEB::callback);
    webServer.begin();

    LOG::info("WEB: Ready.");
    LOG::line();
}

void WEB::received() {
    String message =
        "<html><head> <title>Led Color</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <link rel=\"stylesheet\" href=\"https://meyerweb.com/eric/tools/css/reset/reset.css\"> <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/style.css\"> <script src=\"https://cdn.jsdelivr.net/gh/bebraw/colorjoe/dist/colorjoe.min.js\"></script> <script src=\"https://code.jquery.com/jquery-3.4.1.min.js\"></script></head><body> <div class=\"block\"> <div id=\"picker\"></div> </div> <div id=\"presets\" class=\"block\"> <p>Presets</p> <div id=\"preset-box\"> <a href=\"?hsv=0,0,0\">Turn Off</a> <a href=\"?p=RAINBOW\">Rainbow</a> <a href=\"?p=RAINBOW_STATIC\">Rainbow Static</a> <a href=\"?p=RAINBOW_MOVING\">Rainbow Moving</a> <a href=\"?p=RAINBOW_BLINK\">Rainbow Blink</a> <a href=\"?p=COME_N_GO\">Come N Go</a> <a href=\"?p=BLINK\">Blink</a> <a href=\"?p=FIRE\">Fire</a> </div> </div> <script src=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/script.js\"></script></body></html>";
    if(webServer.arg("v") != "") {
        LED::setValue(webServer.arg("i").toInt());
    }

    //float i_percent = float(value) / 255;

    if(webServer.arg("p") != "") {
        LED::setPreset(LED::str2enum(webServer.arg("p")));
    } else if(webServer.arg("hsv") != "") {
        String hsv = webServer.arg("hsv");

        int h = Util::valueFromStr(hsv, ',', 0).toInt() * 255 / 360;
        int s = Util::valueFromStr(hsv, ',', 1).toInt();
        int v = Util::valueFromStr(hsv, ',', 2).toInt();

        LED::setSolid(CHSV(h, s, v));
    } else if(webServer.arg("c") != "") {
        custom_preset = String(webServer.arg("c"));
        LOG::debug(custom_preset);
        LED::setPreset(Preset::CUSTOM);
    }

    webServer.send(200, "text/html", message);
}

void WEB::callback() {
    webServer.send(200, "text/html", webServer.arg("code"));

    //spotify.get_refresh_token(webServer.arg("code"));
}

void WEB::loop() {
    webServer.handleClient();
}

#endif