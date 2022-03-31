#pragma once
#include "image.h"
#include <vector>
#include <cmath>

namespace matrix_filter {
    template <typename MatrixType>
    Pixel CreatePixel(int32_t x, int32_t y, const Image& image, const std::vector<std::vector<MatrixType>>& matrix) {
        int32_t delta_width = matrix[0].size() / 2;
        int32_t delta_height = matrix.size() / 2;
        MatrixType new_red = 0;
        MatrixType new_green = 0;
        MatrixType new_blue = 0;
        for (int32_t delta_y = -delta_height; delta_y <= delta_height; ++delta_y) {
            for (int32_t delta_x = -delta_width; delta_x <= delta_width; ++delta_x) {
                int32_t pixel_x = std::min(image.GetWidth() - 1, static_cast<uint32_t>(std::max(0, x + delta_x)));
                int32_t pixel_y = std::min(image.GetHeight() - 1, static_cast<uint32_t>(std::max(0, y + delta_y)));
                const Pixel& cur_pixel = image.GetPixel(pixel_x, pixel_y);
                size_t matrix_row = delta_y + delta_height;
                size_t matrix_col = delta_x + delta_width;
                new_red += matrix[matrix_row][matrix_col] * cur_pixel.red;
                new_green += matrix[matrix_row][matrix_col] * cur_pixel.green;
                new_blue += matrix[matrix_row][matrix_col] * cur_pixel.blue;
            }
        }
        uint8_t red = std::min(255, std::max(0, static_cast<int32_t>(round(new_red))));
        uint8_t green = std::min(255, std::max(0, static_cast<int32_t>(round(new_green))));
        uint8_t blue = std::min(255, std::max(0, static_cast<int32_t>(round(new_blue))));
        return Pixel(red, green, blue);
    }
    template <typename MatrixType>
    Image ApplyMatrix(const Image& image, const std::vector<std::vector<MatrixType>>& matrix) {
        Image new_image(image.GetWidth(), image.GetHeight());
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                new_image.SetPixel(x, y, CreatePixel(x, y, image, matrix));
            }
        }
        return new_image;
    }
};

