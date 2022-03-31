#pragma once

#include "filter.h"
#include "image.h"

class NegativeFilter : public Filter {
public:
    NegativeFilter() = default;

    Image Apply(const Image &image) override;

private:
    Pixel CreatePixel(const Image &image, size_t x, size_t y);
};
