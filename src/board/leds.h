#ifndef LEDS_H
#define LEDS_H

#pragma once

#include <Adafruit_NeoPixel.h>

#define LED_PIN     18
#define NUMPIXELS   1
#define BRIGHTNESS  0x10

/**
 * @brief Get a gradient color based on the value and max
 * @param val - The value to get the color from
 * @param max - The max value
 * @return uint32_t - The color
 */
inline uint32_t GradientColor(uint32_t val, uint32_t max) {
    int clamped = constrain(val, 0, max);
    int r = map(clamped, 0, max, 0, 255);
    int g = map(clamped, 0, max, 255, 0);
    int b = 0;

    return Adafruit_NeoPixel::Color(r, g, b);
}

#endif // LEDS_H