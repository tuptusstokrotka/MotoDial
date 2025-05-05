#include "main.h"

void setup() {
    DEBUG_BEGIN(115200);

    // WiFi
    #ifdef WIFI_ENABLE
        WiFi.mode(WIFI_AP);
        WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);

        // OTA
        #ifdef OTA_ENABLE
            ElegantOTA.begin(&server);
            server.begin();
        #endif

        // Web Server
        #ifdef WEB_SERVER_ENABLE
            // WebServer.begin(); //TODO
        #endif
    #endif

    // Board
    board.Init();
}

void loop() {
    // OTA
    #ifdef OTA_ENABLE
        ElegantOTA.loop();
    #endif

    // Web Server
    #ifdef WEB_SERVER_ENABLE
        // WebServer.Update(); //TODO
    #endif

    // Board
    board.Update();
}