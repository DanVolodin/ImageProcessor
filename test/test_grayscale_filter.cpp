#include <catch.hpp>
#include "source.h"
#include "../grayscale_filter.h"

TEST_CASE("Grayscale Filter") {
    GrayscaleFilter gs;
    CHECK(gs.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(29),  Pixel(82),
                                                             Pixel(29),  Pixel(200)},
                                                     {Pixel(150), Pixel(50),
                                                             Pixel(129), Pixel(89)},
                                                     {Pixel(76),  Pixel(0),
                                                             Pixel(100), Pixel(11)},
                                                     {Pixel(255), Pixel(173),
                                                             Pixel(71),  Pixel(250)}}));
}
