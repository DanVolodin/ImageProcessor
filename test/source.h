#pragma once

#include <vector>
#include <string>
#include "../bmp_24.h"
#include "../image.h"
#include "../pixel.h"

namespace source {
    const std::vector<std::vector<Pixel>> ORIGINAL_PIXEL_ARRAY = {{Pixel(0, 0, 255),     Pixel(0, 100, 200),
                                                                          Pixel(0, 50, 0),      Pixel(200, 200, 200)},
                                                                  {Pixel(0, 255, 0),     Pixel(50, 50, 50),
                                                                          Pixel(0, 200, 100),   Pixel(100, 100, 0)},
                                                                  {Pixel(255, 0, 0),     Pixel(0, 0, 0),
                                                                          Pixel(100, 100, 100), Pixel(0, 0, 100)},
                                                                  {Pixel(255, 255, 255), Pixel(50, 250, 100),
                                                                          Pixel(200, 0, 100),   Pixel(250, 250, 250)}};
    const Image ORIGINAL_IMAGE = Image(ORIGINAL_PIXEL_ARRAY);
}