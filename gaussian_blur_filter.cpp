#include <cmath>
#include "gaussian_blur_filter.h"
#include "matrix_filter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
    int32_t radius = ceil(3 * sigma_);
    double sigma_2sqr = 2 * sigma_ * sigma_;
    size_t matrix_size = 2 * radius + 1;
    horizontal_matrix_ = Matrix(1, std::vector<double>(matrix_size));
    vertical_matrix_ = Matrix(matrix_size, std::vector<double>(1));
    double coefficient = sqrt(sigma_2sqr * std::numbers::pi);
    for (int32_t x = -radius; x <= radius; ++x) {
        horizontal_matrix_[0][x + radius] = 1.0 / (coefficient * exp(x * x / sigma_2sqr));
    }
    for (size_t pos = 0; pos < matrix_size; ++pos) {
        vertical_matrix_[pos][0] = horizontal_matrix_[0][pos];
    }
}

Image GaussianBlurFilter::Apply(const Image &image) {
    return matrix_filter::ApplyMatrix(matrix_filter::ApplyMatrix(image, horizontal_matrix_), vertical_matrix_);
}

double GaussianBlurFilter::GetSigma() const {
    return sigma_;
}
