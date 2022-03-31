#include "negative_filter.h"

Image NegativeFilter::Apply(const Image &image) {
    Image new_image(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            new_image.SetPixel(x, y, CreatePixel(image, x, y));
        }
    }
    return new_image;
}

Pixel NegativeFilter::CreatePixel(const Image &image, size_t x, size_t y) {
    Pixel pixel = image.GetPixel(x, y);
    pixel.blue = 255 - pixel.blue;
    pixel.green = 255 - pixel.green;
    pixel.red = 255 - pixel.red;
    return pixel;
}
