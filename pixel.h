#pragma once

#include <cstdint>
#include <fstream>

struct Pixel {
    Pixel() = default;

    Pixel(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {};
    Pixel(uint8_t color) : red(color), green(color), blue(color) {};

    bool operator==(const Pixel &other) const = default;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};
