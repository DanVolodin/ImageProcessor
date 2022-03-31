#include "processor.h"
#include "bmp_24.h"

ImageProcessor::ImageProcessor(std::string input_file, std::string output_file, FilterPtrVector filters) :
        input_file_(std::move(input_file)), output_file_(std::move(output_file)), filters_(std::move(filters)) {}

void ImageProcessor::Run() {
    Image image = bmp_24::ReadBMP(input_file_);
    for (const auto &filter: filters_) {
        image = filter->Apply(image);
    }
    bmp_24::WriteBMP(image, output_file_);
}

std::string ImageProcessor::GetInputFile() const {
    return input_file_;
}

std::string ImageProcessor::GetOutputFile() const {
    return output_file_;
}

FilterPtrVector& ImageProcessor::GetFilters() {
    return filters_;
}
