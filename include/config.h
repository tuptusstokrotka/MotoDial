// HARDWARE CONFIG
    #define OLED_ENABLE
    #define LED_ENABLE

// WIFI CONFIG
    #define WIFI_ENABLE
    // #define PASS_ENABLE
    // At least 8 characters
    #ifdef PASS_ENABLE
        #define WIFI_AP_PASSWORD "password"
    #endif

// WIFI MODULES
    #define OTA_ENABLE
    #define WEB_SERVER_ENABLE

// DEBUG
    #define DEBUGGING                   // Begin Debug Serial
    #define DEBUG_PRINT_ENABLE 1        // Enable Debug Print (must begin Serial)
    #define DEBUG_ANGLE_PRINT_ENABLE 1  // Enable Angle Print
