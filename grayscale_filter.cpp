#include <cmath>
#include "grayscale_filter.h"

Image GrayscaleFilter::Apply(const Image &image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            new_image.SetPixel(x, y, CreatePixel(image, x, y));
        }
    }
    return new_image;
}

Pixel GrayscaleFilter::CreatePixel(const Image &image, size_t x, size_t y) {
    Pixel pixel = image.GetPixel(x, y);
    uint8_t new_color = std::round(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
    pixel.blue = pixel.green = pixel.red = new_color;
    return pixel;
}
