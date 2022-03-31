cmake_minimum_required(VERSION 3.17)
project(Image_Processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(contrib_catch_main
        catch/catch_main.cpp)

target_include_directories(contrib_catch_main
        PUBLIC catch)

add_executable(image_processor
        image_processor.cpp
        processor.cpp
        image.cpp
        bmp_24.cpp
        parser.cpp
        crop_filter.cpp
        grayscale_filter.cpp
        negative_filter.cpp
        sharpening_filter.cpp
        edge_detection_filter.cpp
        gaussian_blur_filter.cpp
        exceptions.cpp
        adaptive_edge_detection_filter.cpp)

add_subdirectory(test)