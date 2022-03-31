#include <iostream>
#include "adaptive_edge_detection_filter.h"
#include "matrix_filter.h"
#include "grayscale_filter.h"

AdaptiveEdgeDetectionFilter::AdaptiveEdgeDetectionFilter(int32_t radius) : radius_(radius), gs_filter_() {}

Image AdaptiveEdgeDetectionFilter::Apply(const Image &image) {
    Image gs_image = gs_filter_.Apply(image);
    Image new_image(image.GetWidth(), image.GetHeight());
    uint32_t area_size = (2 * radius_ + 1) * (2 * radius_ + 1);
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            uint32_t color_sum = 0;
            for (int32_t delta_y = -radius_; delta_y <= radius_; ++delta_y) {
                for (int32_t delta_x = -radius_; delta_x <= radius_; ++delta_x) {
                    int32_t pixel_x = std::min(image.GetWidth() - 1, static_cast<uint32_t>(std::max(0, x + delta_x)));
                    int32_t pixel_y = std::min(image.GetHeight() - 1, static_cast<uint32_t>(std::max(0, y + delta_y)));
                    const Pixel& cur_pixel = gs_image.GetPixel(pixel_x, pixel_y);
                    color_sum += cur_pixel.red;
                }
            }
            int threshold = static_cast<int>(round(color_sum * 1.0 / area_size));
            if (gs_image.GetPixel(x, y).red < threshold) {
                new_image.SetPixel(x, y, Pixel(0));
            } else {
                new_image.SetPixel(x, y, Pixel(255));
            }
        }
    }
    return new_image;
}

int32_t AdaptiveEdgeDetectionFilter::GetRadius() const {
    return radius_;
}
 