#pragma once

#include "filter.h"
#include "image.h"

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma);

    Image Apply(const Image &image) override;

    double GetSigma() const;

private:
    double sigma_ = 0;
    using Matrix = std::vector<std::vector<double>>;
    Matrix horizontal_matrix_;
    Matrix vertical_matrix_;
};