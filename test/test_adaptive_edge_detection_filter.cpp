#include <catch.hpp>
#include "source.h"
#include "../adaptive_edge_detection_filter.h"

TEST_CASE("Adaptive Edge Detection Filter") {
    AdaptiveEdgeDetectionFilter ad_edge_2(2);
    CHECK(ad_edge_2.Apply(source::ORIGINAL_IMAGE) == Image({{Pixel(0),   Pixel(255), Pixel(0),   Pixel(255)},
                                                         {Pixel(255), Pixel(0),   Pixel(255), Pixel(0)},
                                                         {Pixel(0),   Pixel(0),   Pixel(0), Pixel(0)},
                                                         {Pixel(255), Pixel(255), Pixel(0),   Pixel(255)}}));
}

