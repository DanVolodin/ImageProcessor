#include <iostream>
#include "parser.h"
#include "processor.h"


void PrintReference() {
    std::cout << "Image Processor" << std::endl << std::endl;
    std::cout << "usage: image_processor [<input .bmp file>] [<output .bmp file>] [<filters>]" << std::endl
              << std::endl;
    std::cout << "Filters:" << std::endl << std::endl;
    std::cout << "\t-crop <width> <height>      crop filter, <width>, <height> - positive integers" << std::endl;
    std::cout << "\t-gs                         grayscale filter" << std::endl;
    std::cout << "\t-neg                        negative filter" << std::endl;
    std::cout << "\t-sharp                      sharpening filter" << std::endl;
    std::cout << "\t-edge <threshold>           edge detection filter, <threshold> - float in interval [0, 1]"
              << std::endl;
    std::cout << "\t-ad_edge <radius>           adaptive (average) edge detection filter, <radius> - positive integer"
              << std::endl;
    std::cout << "\t-blur <sigma>               gaussian blur filter, <sigma> - positive float" << std::endl;
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        PrintReference();
        return 0;
    }
    Parser parser(argc, argv);
    ImageProcessor image_processor(parser.Parse());
    image_processor.Run();
}
