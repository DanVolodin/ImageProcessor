#include <catch.hpp>
#include "source.h"
#include "../edge_detection_filter.h"

TEST_CASE("Edge Detection Filter") {
    EdgeDetectionFilter edge_1(205);
    CHECK(edge_1.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0),   Pixel(0), Pixel(0),   Pixel(255)},
                                                         {Pixel(255), Pixel(0), Pixel(255), Pixel(0)},
                                                         {Pixel(0),   Pixel(0), Pixel(0),   Pixel(0)},
                                                         {Pixel(255), Pixel(0), Pixel(0),   Pixel(255)}}));

    EdgeDetectionFilter edge_2(50);
    CHECK(edge_2.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0),   Pixel(255), Pixel(0),   Pixel(255)},
                                                         {Pixel(255), Pixel(0),   Pixel(255), Pixel(0)},
                                                         {Pixel(0),   Pixel(0),   Pixel(255), Pixel(0)},
                                                         {Pixel(255), Pixel(255), Pixel(0),   Pixel(255)}}));
}
