#include "sharpening_filter.h"

SharpeningFilter::Matrix SharpeningFilter::SHARPENING_MATRIX({{0,  -1, 0},
                                                              {-1, 5,  -1},
                                                              {0,  -1, 0}});

Image SharpeningFilter::Apply(const Image &image) {
    return matrix_filter::ApplyMatrix(image, SHARPENING_MATRIX);
}
