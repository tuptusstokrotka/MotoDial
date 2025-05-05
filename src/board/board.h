#ifndef BOARD_H
#define BOARD_H

#pragma once

#include "config.h"
#include "angleMeter.h"
#include "display.h"
#include "leds.h"

// I2C
#define SDA 21
#define SCL 22

// Angle Meter
#define MAX_ANGLE 70 //DEBUG

// Button
#define BUTTON_PIN 19

enum class State {
    IDLE,
    CALIBRATING,
    READY,
    ERROR
};

class Board {
private:
    State state = State::IDLE;

    // Components
    AngleMeter angleMeter;
    Display display;
    Adafruit_NeoPixel* pixels = nullptr;

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
    // inline void InvertDirection()                { angleMeter.InvertDirection(); }
    // inline void SetHoldTime(uint32_t holdTime)   { angleMeter.SetHoldTime(holdTime); }
    // inline void SetAlpha(uint32_t alpha)         { angleMeter.SetAlpha(alpha); }
};

#endif // BOARD_H