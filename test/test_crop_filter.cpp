#include <catch.hpp>
#include "source.h"
#include "../crop_filter.h"

TEST_CASE("Crop Filter") {
    CropFilter crop_1(3, 2);
    CHECK(crop_1.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0, 0, 255), Pixel(0, 100, 200), Pixel(0, 50, 0)},
                                                         {Pixel(0, 255, 0), Pixel(50, 50, 50),  Pixel(0, 200, 100)}}));

    CropFilter crop_2(15, 10);
    CHECK(crop_2.Apply(source::ORIGINAL_IMAGE) == source::ORIGINAL_IMAGE);

    CropFilter crop_3(10, 1);
    CHECK(crop_3.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0, 0, 255), Pixel(0, 100, 200),
                                                          Pixel(0, 50, 0), Pixel(200, 200, 200)}}));
}