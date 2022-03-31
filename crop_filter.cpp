#include "crop_filter.h"

CropFilter::CropFilter(uint32_t width, uint32_t height) : width_(width), height_(height) {}

Image CropFilter::Apply(const Image &image) {
    Image new_image(image);
    new_image.SetHeight(height_);
    new_image.SetWidth(width_);
    return new_image;
}

uint32_t CropFilter::GetWidth() const {
    return width_;
}

uint32_t CropFilter::GetHeight() const {
    return height_;
}
