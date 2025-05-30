#ifndef BOARD_H
#define BOARD_H

#pragma once

#include "config.h"
#include "angleMeter.h"
#include "display.h"
#include "leds.h"
#include "FastButton.h"

// I2C
#define SDA (int)6
#define SCL (int)7

// Button
#define BUTTON_PIN (int)1

// Led
#define LED_PIN     (int)0
#define NUMPIXELS   (int)1
#define BRIGHTNESS  (int)0x10

// Angle Meter
#define MAX_ANGLE 70 //DEBUG

enum class State {
    IDLE,
    CALIBRATING,
    READY,
    ERROR
};

class Board {
private:
    State state = State::IDLE;
    uint16_t errorCode = 0x00;

    // Components
    FastButton button;
    AngleMeter angleMeter;
    Display display;
    Adafruit_NeoPixel pixels;

    inline State GetState() { return state; }

    void LedUpdate();
    void DisplayUpdate();
    void ButtonUpdate();

public:
    Board();
    ~Board();

    void Init();
    void Update();
    void Calibrate();

    inline void SetState(State state) { this->state = state; }

    // API
    inline void InvertDirection(bool invert) { angleMeter.InvertDirection(invert); }
    inline void SetHoldTime(uint32_t holdTime) { angleMeter.SetHoldTime(holdTime); }
    inline void SetAlpha(uint32_t alpha) { angleMeter.SetAlpha(alpha); }

    // API - LED ONLY
    // inline void SetMaxAngle(uint32_t maxAngle) { .....SetMaxAngle(maxAngle); }
};

#endif // BOARD_H