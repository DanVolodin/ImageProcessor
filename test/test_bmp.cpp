#include <catch.hpp>
#include "source.h"

const char *TEST_INPUT_FILE = "../../test/images/test_input.bmp";
const char *TEST_OUTPUT_FILE = "../../test/images/test_output.bmp";
const char *TEST_8BIT_BMP_FILE = "../../test/images/test_8bit.bmp";
const char *TEST_PNG_FILE = "../../test/images/test_png.png";
const char *TEST_NONEXISTENT_FILE = "../../test/images/test_png.bmp";
const uint32_t ORIGINAL_BMP_SIZE = 102;
const uint32_t ORIGINAL_BITMAP_SIZE = 48;
const size_t BMP_SIZE_OFFSET = 2;
const size_t BITMAP_SIZE_OFFSET = 34;

TEST_CASE("Read BMP") {
    SECTION("Correct 24-bit BMP"){
        Image image = bmp_24::ReadBMP(TEST_INPUT_FILE);
        CHECK(image == source::ORIGINAL_IMAGE);
    }
    SECTION("Invalid 8-bit BMP") {
        std::string message = "../../test/images/test_8bit.bmp is a BMP file, but not a 24-bit BMP";
        CHECK_THROWS_WITH(bmp_24::ReadBMP(TEST_8BIT_BMP_FILE), message);
    }
    SECTION("Invalid PNG") {
        std::string message = "../../test/images/test_png.png is not a BMP file";
        CHECK_THROWS_WITH(bmp_24::ReadBMP(TEST_PNG_FILE), message);
    }
    SECTION("Non-existent file") {
        std::string message = "Failed to open file: ../../test/images/test_png.bmp";
        CHECK_THROWS_WITH(bmp_24::ReadBMP(TEST_NONEXISTENT_FILE), message);
    }
}

TEST_CASE("Write BMP") {
    bmp_24::WriteBMP(source::ORIGINAL_IMAGE, TEST_OUTPUT_FILE);
    Image image = bmp_24::ReadBMP(TEST_OUTPUT_FILE);
    CHECK(image == source::ORIGINAL_IMAGE);
    std::ifstream input(TEST_OUTPUT_FILE, std::ios::in | std::ios::binary);
    uint32_t bmp_size = 0;
    uint32_t bitmap_size = 0;
    input.seekg(BMP_SIZE_OFFSET, std::ios::beg);
    input.read(reinterpret_cast<char *>(&bmp_size), sizeof(bmp_size));
    input.seekg(BITMAP_SIZE_OFFSET, std::ios::beg);
    input.read(reinterpret_cast<char *>(&bitmap_size), sizeof(bitmap_size));
    CHECK(bmp_size == ORIGINAL_BMP_SIZE);
    CHECK(bitmap_size == ORIGINAL_BITMAP_SIZE);
}

