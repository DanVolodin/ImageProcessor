#pragma once

#include <string>
#include <vector>
#include <memory>
#include "filter.h"

using FilterPtrVector = std::vector<std::unique_ptr<Filter>>;

class ImageProcessor {
public:
    ImageProcessor(std::string input_file, std::string output_file, FilterPtrVector filters);

    std::string GetInputFile() const;
    std::string GetOutputFile() const;
    FilterPtrVector& GetFilters();

    void Run();

private:
    std::string input_file_;
    std::string output_file_;
    FilterPtrVector filters_;
};
