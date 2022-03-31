#include <catch.hpp>
#include "source.h"
#include "../sharpening_filter.h"

TEST_CASE("Sharpening Filter") {
    SharpeningFilter sharp;
    CHECK(sharp.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0, 0, 255),     Pixel(0, 255, 255),
                                                                Pixel(0, 0, 0),       Pixel(255, 255, 255)},
                                                        {Pixel(0, 255, 0),     Pixel(250, 0, 0),
                                                                Pixel(0, 255, 255),   Pixel(200, 0, 0)},
                                                        {Pixel(255, 0, 0),     Pixel(0, 0, 0),
                                                                Pixel(255, 255, 200), Pixel(0, 0, 50)},
                                                        {Pixel(255, 255, 255), Pixel(0, 255, 45),
                                                                Pixel(255, 0, 0),     Pixel(255, 255, 255)}}));
}
