#include "config.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include "board/board.h"

#pragma region DEBUG
    #ifndef DEBUGGING
    #define DEBUGGING 0
    #undef DEBUG_PRINT_ENABLE
    #endif
    #ifndef DEBUG_PRINT_ENABLE
    #define DEBUG_PRINT_ENABLE 0
    #endif

    #if DEBUG_PRINT_ENABLE == 1
        #define DEBUG_BEGIN(baud)   Serial.begin(baud);
        #define DEBUG_PRINT(s)      Serial.print(s);
        #define DEBUG_PRINTLN(s)    Serial.println(s);
    #else
        #define DEBUG_BEGIN(baud)   ;
        #define DEBUG_PRINT(s)      ;
        #define DEBUG_PRINTLN(s)    ;
    #endif
#pragma endregion

AsyncWebServer server(80);
// WebServer WebServer; //TODO - maybe redundant
Board board;