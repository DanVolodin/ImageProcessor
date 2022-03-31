#include "image.h"

Image::Image(uint32_t width, uint32_t height) : width_(width), height_(height),
                                                pixel_array_(height, std::vector<Pixel>(width)) {
}

Image::Image(const PixelTable &pixel_array) : pixel_array_(pixel_array) {
    height_ = pixel_array_.size();
    if (height_ > 0) {
        width_ = pixel_array_[0].size();
    }
}

uint32_t Image::GetWidth() const {
    return width_;
}

void Image::SetWidth(uint32_t width) {
    width_ = std::min(width, width_);
    for (auto &row: pixel_array_) {
        row.resize(width_);
    }
}

uint32_t Image::GetHeight() const {
    return height_;
}

void Image::SetHeight(uint32_t height) {
    height_ = std::min(height, height_);
    pixel_array_.resize(height_);
}

Pixel Image::GetPixel(size_t x, size_t y) const {
    return pixel_array_[y][x];
}

void Image::SetPixel(size_t x, size_t y, Pixel pixel) {
    pixel_array_[y][x] = std::move(pixel);
}

void Image::Reverse() {
    std::reverse(pixel_array_.begin(), pixel_array_.end());
}
