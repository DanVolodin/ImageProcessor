#pragma once

#include <vector>
#include "pixel.h"

using PixelTable = std::vector<std::vector<Pixel>>;

class Image {
public:
    Image() = default;

    Image(const Image &other) = default;

    Image(uint32_t width, uint32_t height);

    Image(const PixelTable &pixel_array);

    uint32_t GetWidth() const;

    void SetWidth(uint32_t width);

    uint32_t GetHeight() const;

    void SetHeight(uint32_t height);

    Pixel GetPixel(size_t x, size_t y) const;

    void SetPixel(size_t x, size_t y, Pixel pixel);

    void Reverse();

    bool operator==(const Image &other) const = default;

private:
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    PixelTable pixel_array_;
};
