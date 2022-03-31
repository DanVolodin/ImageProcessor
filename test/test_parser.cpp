#include <catch.hpp>
#include <iostream>
#include "../parser.h"
#include "../processor.h"
#include "../crop_filter.h"
#include "../grayscale_filter.h"
#include "../negative_filter.h"
#include "../sharpening_filter.h"
#include "../edge_detection_filter.h"
#include "../gaussian_blur_filter.h"
#include "../adaptive_edge_detection_filter.h"

using Argv = const char*;

TEST_CASE("Parsing Files") {
    SECTION("Correct arguments") {
        int argc = 3;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");
    }
    SECTION("No output file") {
        int argc = 2;
        Argv argv[] = {"image_processor", "input.bmp"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for saving bmp: 0 (1 expected)");
    }
    SECTION("No arguments") {
        int argc = 1;
        Argv argv[] = {"image_processor"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for reading and saving bmp: 0 (2 expected)");
    }
}

TEST_CASE("Parsing Crop") {
    SECTION("Valid crop arguments") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "1000", "500"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 1);

        auto* crop_filter = dynamic_cast<CropFilter*>(filters[0].get());
        CHECK(crop_filter != nullptr);
        CHECK(crop_filter->GetWidth() == 1000);
        CHECK(crop_filter->GetHeight() == 500);
    }
    SECTION("0 arguments") {
        int argc = 4;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for Crop filter: 0 (2 expected)");
    }
    SECTION("1 argument") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "1000"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for Crop filter: 1 (2 expected)");
    }
    SECTION("Float width") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "5.5", "1000"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid width type");
    }
    SECTION("Not integer width") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "-gs", "1000"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid width type");
    }
    SECTION("Not positive width") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "0", "1000"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid width value");
    }
    SECTION("Float height") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "1000", "0.01"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid height type");
    }
    SECTION("Not integer height") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "1000", "one"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid height type");
    }
    SECTION("Not positive height") {
        int argc = 6;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "1000", "-1000"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Crop: invalid height value");
    }
}

TEST_CASE("Parsing Grayscale, Negative, Sharpening") {
    int argc = 6;
    Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-gs", "-sharp", "-neg"};
    Parser parser(argc, argv);
    ImageProcessor processor(parser.Parse());

    CHECK(processor.GetInputFile() == "input.bmp");
    CHECK(processor.GetOutputFile() == "output.bmp");

    FilterPtrVector& filters(processor.GetFilters());
    REQUIRE(filters.size() == 3);

    auto* gs_filter = dynamic_cast<GrayscaleFilter*>(filters[0].get());
    CHECK(gs_filter != nullptr);

    auto* sharp_filter = dynamic_cast<SharpeningFilter*>(filters[1].get());
    CHECK(sharp_filter != nullptr);

    auto* neg_filter = dynamic_cast<NegativeFilter*>(filters[2].get());
    CHECK(neg_filter != nullptr);
}

TEST_CASE("Parsing Edge Detection") {
    SECTION("Valid Edge Detection arguments") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-edge", "0.69"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 1);

        auto* edge_filter = dynamic_cast<EdgeDetectionFilter*>(filters[0].get());
        CHECK(edge_filter != nullptr);
        CHECK(edge_filter->GetThreshold() == 176);
    }
    SECTION("0 arguments") {
        int argc = 4;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-edge"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for Edge Detection filter: 0 (1 expected)");
    }
    SECTION("Threshold < 0") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-edge", "-1.43"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Edge Detection: invalid threshold value");
    }
    SECTION("Threshold > 1") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-edge", "100"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Edge Detection: invalid threshold value");
    }
    SECTION("Not float threshold") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-edge", "-crop", "100", "200"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Edge Detection: invalid threshold type");
    }
}

TEST_CASE("Parsing Gaussian Blur") {
    SECTION("Valid integer Gaussian Blur argument") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "5"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 1);

        auto* blur_filter = dynamic_cast<GaussianBlurFilter*>(filters[0].get());
        CHECK(blur_filter != nullptr);
        CHECK(blur_filter->GetSigma() == 5);
    }
    SECTION("Valid float Gaussian Blur argument") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "0.005"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 1);

        auto* blur_filter = dynamic_cast<GaussianBlurFilter*>(filters[0].get());
        CHECK(blur_filter != nullptr);
        CHECK(blur_filter->GetSigma() == 0.005);
    }
    SECTION("0 arguments") {
        int argc = 4;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for Gaussian Blur filter: 0 (1 expected)");
    }
    SECTION("Sigma = 0") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "0"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Gaussian Blur: invalid sigma value");
    }
    SECTION("Sigma < 0") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "-0.01"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Gaussian Blur: invalid sigma value");
    }
    SECTION("Invalid sigma type") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "twenty-two"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Gaussian Blur: invalid sigma type");
    }
}

TEST_CASE("Parsing Adaptive Edge Detection") {
    SECTION("Valid Adaptive Edge Detection argument") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-ad_edge", "5"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 1);

        auto* blur_filter = dynamic_cast<AdaptiveEdgeDetectionFilter*>(filters[0].get());
        CHECK(blur_filter != nullptr);
        CHECK(blur_filter->GetRadius() == 5);
    }
    SECTION("0 arguments") {
        int argc = 4;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-ad_edge"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Not enough arguments for Adaptive Edge Detection filter: 0 (1 expected)");
    }
    SECTION("Float Radius") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-ad_edge", "0.05"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Adaptive Edge Detection: invalid radius type");
    }
    SECTION("Radius < 0") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-ad_edge", "-10"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Adaptive Edge Detection: invalid radius value");
    }
    SECTION("Invalid radius type") {
        int argc = 5;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-ad_edge", "-ad_edge"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "Adaptive Edge Detection: invalid radius type");
    }
}

TEST_CASE("Parsing Filters") {
    SECTION("Valid 1") {
        int argc = 9;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "5", "-gs", "-crop", "500", "100"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 3);

        auto* blur_filter = dynamic_cast<GaussianBlurFilter *>(filters[0].get());
        CHECK(blur_filter != nullptr);
        CHECK(blur_filter->GetSigma() == 5);

        auto* gs_filter = dynamic_cast<GrayscaleFilter *>(filters[1].get());
        CHECK(gs_filter != nullptr);

        auto* crop_filter = dynamic_cast<CropFilter*>(filters[2].get());
        CHECK(crop_filter != nullptr);
        CHECK(crop_filter->GetWidth() == 500);
        CHECK(crop_filter->GetHeight() == 100);
    }
    SECTION("Valid 2") {
        int argc = 8;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-gs", "-sharp", "-edge", "0.2", "-gs"};
        Parser parser(argc, argv);
        ImageProcessor processor(parser.Parse());

        CHECK(processor.GetInputFile() == "input.bmp");
        CHECK(processor.GetOutputFile() == "output.bmp");

        FilterPtrVector& filters(processor.GetFilters());
        REQUIRE(filters.size() == 4);

        auto* gs_filter_1 = dynamic_cast<GrayscaleFilter*>(filters[0].get());
        CHECK(gs_filter_1 != nullptr);

        auto* sharp_filter = dynamic_cast<SharpeningFilter*>(filters[1].get());
        CHECK(sharp_filter != nullptr);

        auto* edge_filter = dynamic_cast<EdgeDetectionFilter*>(filters[2].get());
        CHECK(edge_filter != nullptr);
        CHECK(edge_filter->GetThreshold() == 51);

        auto* gs_filter_2 = dynamic_cast<GrayscaleFilter*>(filters[3].get());
        CHECK(gs_filter_2 != nullptr);
    }
    SECTION("Invalid filter name") {
        int argc = 8;
        Argv argv[] = {"image_processor", "input.bmp", "output.bmp", "-blur", "5", "-gs", "-sharpening", "-neg"};
        Parser parser(argc, argv);
        CHECK_THROWS_WITH(parser.Parse(), "No filter called \"-sharpening\"");
    }
}
