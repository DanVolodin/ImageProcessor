#pragma once

#include "filter.h"
#include "image.h"
#include "grayscale_filter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(uint8_t threshold);

    Image Apply(const Image &image) override;

    uint8_t GetThreshold() const;

private:
    uint8_t threshold_;
    GrayscaleFilter gs_filter_;
    using Matrix = const std::vector<std::vector<int>>;
    static Matrix EDGE_DETECTION_MATRIX;
};
