#include <catch.hpp>
#include "source.h"
#include "../negative_filter.h"

TEST_CASE("Negative Filter") {
    NegativeFilter neg;
    CHECK(neg.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(255, 255, 0), Pixel(255, 155, 55),
                                                              Pixel(255, 205, 255), Pixel(55, 55, 55)},
                                                      {Pixel(255, 0, 255), Pixel(205, 205, 205),
                                                              Pixel(255, 55, 155),  Pixel(155, 155, 255)},
                                                      {Pixel(0, 255, 255), Pixel(255, 255, 255),
                                                              Pixel(155, 155, 155), Pixel(255, 255, 155)},
                                                      {Pixel(0, 0, 0),     Pixel(205, 5, 155),
                                                              Pixel(55, 255, 155),  Pixel(5, 5, 5)}}));
}
