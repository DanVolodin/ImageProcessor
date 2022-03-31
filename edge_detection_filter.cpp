#include "edge_detection_filter.h"
#include "grayscale_filter.h"
#include "matrix_filter.h"

EdgeDetectionFilter::Matrix EdgeDetectionFilter::EDGE_DETECTION_MATRIX({{0,  -1, 0},
                                                                        {-1, 4,  -1},
                                                                        {0,  -1, 0}});

EdgeDetectionFilter::EdgeDetectionFilter(uint8_t threshold) : threshold_(threshold), gs_filter_() {}

Image EdgeDetectionFilter::Apply(const Image &image) {
    Image new_image = matrix_filter::ApplyMatrix(gs_filter_.Apply(image), EDGE_DETECTION_MATRIX);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            if (new_image.GetPixel(x, y).red > threshold_) {
                new_image.SetPixel(x, y, Pixel(255, 255, 255));
            } else {
                new_image.SetPixel(x, y, Pixel());
            }
        }
    }
    return new_image;
}

uint8_t EdgeDetectionFilter::GetThreshold() const {
    return threshold_;
}
