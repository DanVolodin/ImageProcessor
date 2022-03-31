#pragma once

#include "image.h"
#include <string>

namespace bmp_24 {
    Image ReadBMP(const std::string &input_file);

    void WriteBMP(const Image &image, const std::string &output_file);
}
