#include "parser.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "exceptions.h"
#include "adaptive_edge_detection_filter.h"
#include <string>
#include <cmath>

Parser::Parser(int argc, const char *argv[]) : argc_(argc), argv_(argv) {
    commands_["-crop"] = [&]() { ParseCropFilter(); };
    commands_["-gs"] = [&]() { ParseGrayscaleFilter(); };
    commands_["-neg"] = [&]() { ParseNegativeFilter(); };
    commands_["-sharp"] = [&]() { ParseSharpeningFilter(); };
    commands_["-edge"] = [&]() { ParseEdgeDetectionFilter(); };
    commands_["-blur"] = [&]() { ParseGaussianBlurFilter(); };
    commands_["-ad_edge"] = [&]() { ParseAdaptiveEdgeDetectionFilter(); };
}

ImageProcessor Parser::Parse() {
    if (argc_ == 1) {
        throw NotEnoughArgumentsException("reading and saving bmp", 0, 2);
    }
    if (argc_ == 2) {
        throw NotEnoughArgumentsException("saving bmp", 0, 1);
    }
    input_file_ = argv_[1];
    output_file_ = argv_[2];
    while (pos_ < argc_) {
        ParseFilter();
    }
    return ImageProcessor(input_file_, output_file_, std::move(filters_));
}

void Parser::ParseFilter() {
    std::string filter_name(argv_[pos_]);
    auto it = commands_.find(filter_name);
    if (it == commands_.end()) {
        std::string message = "No filter called \"" + filter_name + "\"";
        throw std::invalid_argument(message);
    }
    ++pos_;
    it->second();
}

void Parser::ParseCropFilter() {
    if (pos_ + 2 > argc_) {
        throw NotEnoughArgumentsException("Crop filter", argc_ - pos_, 2);
    }
    int32_t width = 0;
    try {
        width = std::stoll(argv_[pos_]);
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Crop: invalid width type");
    }
    if (std::to_string(width) != argv_[pos_]) {
        throw std::invalid_argument("Crop: invalid width type");
    }
    if (width < 1) {
        throw std::invalid_argument("Crop: invalid width value");
    }
    int32_t height = 0;
    try {
        height = std::stoll(argv_[pos_ + 1]);
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Crop: invalid height type");
    }
    if (std::to_string(height) != argv_[pos_ + 1]) {
        throw std::invalid_argument("Crop: invalid height type");
    }
    if (height < 1) {
        throw std::invalid_argument("Crop: invalid height value");
    }
    filters_.push_back(std::make_unique<CropFilter>(width, height));
    pos_ += 2;
}

void Parser::ParseGrayscaleFilter() {
    filters_.push_back(std::make_unique<GrayscaleFilter>());
}

void Parser::ParseNegativeFilter() {
    filters_.push_back(std::make_unique<NegativeFilter>());
}

void Parser::ParseSharpeningFilter() {
    filters_.push_back(std::make_unique<SharpeningFilter>());
}

void Parser::ParseEdgeDetectionFilter() {
    if (pos_ + 1 > argc_) {
        throw NotEnoughArgumentsException("Edge Detection filter", 0, 1);
    }
    float threshold;
    try {
        threshold = std::stof(argv_[pos_]);
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Edge Detection: invalid threshold type");
    }
    if (threshold < 0 || threshold > 1) {
        throw std::invalid_argument("Edge Detection: invalid threshold value");
    }
    filters_.push_back(std::make_unique<EdgeDetectionFilter>(round(255 * threshold)));
    ++pos_;
}

void Parser::ParseGaussianBlurFilter() {
    if (pos_ + 1 > argc_) {
        throw NotEnoughArgumentsException("Gaussian Blur filter", 0, 1);
    }
    double sigma;
    try {
        sigma = std::stod(argv_[pos_]);
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Gaussian Blur: invalid sigma type");
    }
    if (sigma <= 0) {
        throw std::invalid_argument("Gaussian Blur: invalid sigma value");
    }
    filters_.push_back(std::make_unique<GaussianBlurFilter>(sigma));
    ++pos_;
}

void Parser::ParseAdaptiveEdgeDetectionFilter() {
    if (pos_ + 1 > argc_) {
        throw NotEnoughArgumentsException("Adaptive Edge Detection filter", 0, 1);
    }
    int32_t radius;
    try {
        radius = std::stoll(argv_[pos_]);
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Adaptive Edge Detection: invalid radius type");
    }
    if (std::to_string(radius) != argv_[pos_]) {
        throw std::invalid_argument("Adaptive Edge Detection: invalid radius type");
    }
    if (radius <= 0) {
        throw std::invalid_argument("Adaptive Edge Detection: invalid radius value");
    }
    filters_.push_back(std::make_unique<AdaptiveEdgeDetectionFilter>(radius));
    ++pos_;
}
