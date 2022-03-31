add_executable(tests
        ../image.cpp
        ../processor.cpp
        ../bmp_24.cpp
        ../parser.cpp
        ../exceptions.cpp
        ../crop_filter.cpp
        ../grayscale_filter.cpp
        ../negative_filter.cpp
        ../sharpening_filter.cpp
        ../edge_detection_filter.cpp
        ../gaussian_blur_filter.cpp
        ../adaptive_edge_detection_filter.cpp
        test_bmp.cpp
        test_parser.cpp
        test_crop_filter.cpp
        test_negative_filter.cpp
        test_grayscale_filter.cpp
        test_sharpening_filter.cpp
        test_edge_detection_filter.cpp
        test_gaussian_blur_filter.cpp
        test_adaptive_edge_detection_filter.cpp)

target_link_libraries(tests contrib_catch_main)
