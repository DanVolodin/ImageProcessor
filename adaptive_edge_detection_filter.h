#pragma once
#include "filter.h"
#include "grayscale_filter.h"

class AdaptiveEdgeDetectionFilter : public Filter {
public:
    explicit AdaptiveEdgeDetectionFilter(int32_t radius);

    Image Apply(const Image &image) override;

    int32_t GetRadius() const;

private:
    int32_t radius_ = 0;
    GrayscaleFilter gs_filter_;
};