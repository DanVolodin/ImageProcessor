#pragma once

#include "filter.h"
#include "image.h"

class CropFilter : public Filter {
public:
    explicit CropFilter(uint32_t width, uint32_t height);

    Image Apply(const Image &image) override;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

private:
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};