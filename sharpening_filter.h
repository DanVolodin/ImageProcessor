#pragma once

#include "filter.h"
#include "image.h"
#include "matrix_filter.h"

class SharpeningFilter : public Filter {
public:
    SharpeningFilter() = default;

    Image Apply(const Image &image) override;

private:
    using Matrix = std::vector<std::vector<int>>;
    static Matrix SHARPENING_MATRIX;
};