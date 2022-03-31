#include <catch.hpp>
#include "source.h"
#include "../gaussian_blur_filter.h"

TEST_CASE("Gaussian Blur Filter") {
    GaussianBlurFilter blur_1(2);
    CHECK(blur_1.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(58, 85, 153),   Pixel(68, 97, 142),
                                                                 Pixel(87, 113, 135),  Pixel(111, 130, 137)},
                                                         {Pixel(88, 108, 138),  Pixel(91, 113, 131),
                                                                 Pixel(101, 121, 129), Pixel(117, 131, 133)},
                                                         {Pixel(125, 135, 138), Pixel(121, 133, 133),
                                                                 Pixel(124, 134, 134), Pixel(134, 140, 140)},
                                                         {Pixel(160, 163, 153), Pixel(151, 156, 146),
                                                                 Pixel(151, 153, 149), Pixel(158, 156, 158)}}));

    GaussianBlurFilter blur_2(0.25);
    CHECK(blur_2.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0, 0, 255),     Pixel(0, 255, 255),
                                                                 Pixel(0, 128, 0),     Pixel(255, 255, 255)},
                                                         {Pixel(0, 255, 0),     Pixel(128, 128, 128),
                                                                 Pixel(0, 255, 255),   Pixel(255, 255, 0)},
                                                         {Pixel(255, 0, 0),     Pixel(0, 0, 0),
                                                                 Pixel(255, 255, 255), Pixel(0, 0, 255)},
                                                         {Pixel(255, 255, 255), Pixel(128, 255, 255),
                                                                 Pixel(255, 0, 255),   Pixel(255, 255, 255)}}));
}


