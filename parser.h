#pragma once

#include <memory>
#include <functional>
#include "filter.h"
#include "processor.h"

using FilterPtrVector = std::vector<std::unique_ptr<Filter>>;

class Parser {
public:
    Parser(int argc, const char *argv[]);

    ImageProcessor Parse();

private:
    void ParseFilter();

    void ParseCropFilter();

    void ParseGrayscaleFilter();

    void ParseNegativeFilter();

    void ParseSharpeningFilter();

    void ParseEdgeDetectionFilter();

    void ParseGaussianBlurFilter();

    void ParseAdaptiveEdgeDetectionFilter();

    int pos_ = 3;
    const int argc_ = 0;
    const char **argv_;

    std::string input_file_;
    std::string output_file_;

    FilterPtrVector filters_;

    using Command = std::function<void()>;
    std::unordered_map<std::string, Command> commands_;
};

