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
        "<html><head> <title>Led Color</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <link rel=\"stylesheet\" href=\"https://meyerweb.com/eric/tools/css/reset/reset.css\"> <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/style.css\"> <script src=\"https://cdn.jsdelivr.net/gh/bebraw/colorjoe/dist/colorjoe.min.js\"></script> <script src=\"https://code.jquery.com/jquery-3.4.1.min.js\"></script></head><body> <div class=\"block\"> <div id=\"picker\"></div> </div> <div id=\"presets\" class=\"block\"> <p>Presets</p> <div id=\"preset-box\"> <a href=\"?hsv=0,0,0\">Turn Off</a> <a href=\"?p=2\">Rainbow</a> <a href=\"?p=3\">Rainbow Static</a> <a href=\"?p=4\">Rainbow Moving</a> <a href=\"?p=7\">Rainbow Blink</a> <a href=\"?p=5\">Come N Go</a> <a href=\"?p=6\">Blink</a> <a href=\"?p=9\">Fire</a> </div> </div> <script src=\"https://cdn.jsdelivr.net/gh/ETblaky/RoomLED@latest/src/web/script.js\"></script></body></html>";
    if(webServer.arg("v") != "") {
        LED::setValue(webServer.arg("i").toInt());
    }

    //float i_percent = float(value) / 255;

    if(webServer.arg("p") != "") {
        std::map<PresetType, Preset *>::iterator it(LED::preset_list.begin());
        std::advance(it, webServer.arg("p").toInt());
        LED::setPreset(it->first);
    } else if(webServer.arg("hsv") != "") {
        String hsv = webServer.arg("hsv");

        int h = Util::valueFromStr(hsv, ',', 0).toInt() * 255 / 360;
        int s = Util::valueFromStr(hsv, ',', 1).toInt();
        int v = Util::valueFromStr(hsv, ',', 2).toInt();

        LED::value = v;
        LED::setPreset(PresetType::SOLID, true, [&]() { LED::p_solid.set_color(CHSV(h, s, v)); });
    } else if(webServer.arg("c") != "") {
        LED::p_custom.custom_preset = String(webServer.arg("c"));
        LOG::debug(LED::p_custom.custom_preset);
        LED::setPreset(PresetType::CUSTOM);
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