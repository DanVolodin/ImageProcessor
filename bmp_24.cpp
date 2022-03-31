#include "bmp_24.h"
#include "exceptions.h"

// BMP Header
const uint16_t ID_FIELD = 0x4d42;
const uint32_t PIXEL_ARRAY_OFFSET = 54;
// DIB Header
const uint32_t PIXEL_ARRAY_SIZE_OFFSET = 18;
const uint32_t DIP_HEADER_SIZE = 40;
const uint16_t COLOR_PLANES_NUMBER = 1;
const uint16_t BITS_PER_PIXEL = 24;
const uint32_t BYTES_PER_PIXEL = 3;
const uint32_t COMPRESSION = 0;
const uint32_t HORIZONTAL_RESOLUTION = 0x00000b13;
const uint32_t VERTICAL_RESOLUTION = 0x00000b13;
const uint32_t PALETTE_COLOR_NUMBER = 0;
const uint32_t IMPORTANT_COLORS = 0;

const size_t BMP_FORMAT_OFFSET = 28;

template<typename T>
void Read(std::ifstream &input, T &var) {
    input.read(reinterpret_cast<char *>(&var), sizeof(var));
}

template<>
void Read(std::ifstream &input, Pixel &pixel) {
    Read(input, pixel.blue);
    Read(input, pixel.green);
    Read(input, pixel.red);
}

void SkipFromBegin(std::ifstream &input, size_t bytes_number) {
    input.seekg(bytes_number, std::ios::beg);
}

void SkipFromCurrent(std::ifstream &input, size_t bytes_number) {
    input.seekg(bytes_number, std::ios::cur);
}

template<typename T>
void Write(std::ofstream &output, const T &var) {
    output.write(reinterpret_cast<const char *>(&var), sizeof(var));
}

template<>
void Write(std::ofstream &output, const Pixel &var) {
    Write(output, var.blue);
    Write(output, var.green);
    Write(output, var.red);
}

void WriteZeros(std::ofstream &output, size_t bytes_number) {
    uint8_t zero_byte = 0;
    for (size_t i = 0; i < bytes_number; ++i) {
        Write(output, zero_byte);
    }
}

size_t CountPadding(uint32_t pixels_in_row) {
    size_t bitmap_row_length = pixels_in_row * BYTES_PER_PIXEL;
    size_t bitmap_row_padding = (4 - bitmap_row_length % 4) % 4;
    return bitmap_row_padding;
}

void CheckFileIsValidBMP(std::ifstream& input, const std::string& file_name) {
    uint16_t id_field = 0;
    Read(input, id_field);
    if (id_field != ID_FIELD) {
        throw std::invalid_argument(file_name + " is not a BMP file");
    }
    uint16_t bits_per_pixel = 0;
    SkipFromBegin(input, BMP_FORMAT_OFFSET);
    Read(input, bits_per_pixel);
    if (bits_per_pixel != BITS_PER_PIXEL) {
        throw std::invalid_argument(file_name + " is a BMP file, but not a 24-bit BMP");
    }
}

Image bmp_24::ReadBMP(const std::string &input_file) {
    std::ifstream input(input_file, std::ios::in | std::ios::binary);
    uint32_t width = 0;
    int32_t height = 0;
    bool reversed = true;
    Image image;
    if (!input.is_open()) {
        throw FileOpenFailedException(input_file);
    }
    CheckFileIsValidBMP(input, input_file);
    SkipFromBegin(input, PIXEL_ARRAY_SIZE_OFFSET);
    Read(input, width);
    Read(input, height);
    if (height < 0) {
        reversed = false;
        height = -height;
    }
    image = Image(width, height);
    SkipFromBegin(input, PIXEL_ARRAY_OFFSET);
    size_t bitmap_row_padding = CountPadding(width);
    Pixel pixel_read;
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            Read(input, pixel_read);
            image.SetPixel(col, row, pixel_read);
        }
        SkipFromCurrent(input, bitmap_row_padding);
    }
    input.close();
    if (reversed) {
        image.Reverse();
    }
    return image;
}

void bmp_24::WriteBMP(const Image &image, const std::string &output_file) {
    std::ofstream output(output_file, std::ios::out | std::ios::binary);
    uint32_t image_width = image.GetWidth();
    int32_t image_height = image.GetHeight();
    size_t bitmap_row_padding = CountPadding(image_width);
    uint32_t raw_bitmap_size = image_height * image_width * BYTES_PER_PIXEL + image_height * bitmap_row_padding;
    uint32_t bmp_size = PIXEL_ARRAY_OFFSET + raw_bitmap_size;
    if (!output.is_open()) {
        throw FileOpenFailedException(output_file);
    }
    // BMP Header
    Write(output, ID_FIELD);
    Write(output, bmp_size);
    WriteZeros(output, 4);
    Write(output, PIXEL_ARRAY_OFFSET);
    // DIB Header
    Write(output, DIP_HEADER_SIZE);
    Write(output, image_width);
    Write(output, -image_height);
    Write(output, COLOR_PLANES_NUMBER);
    Write(output, BITS_PER_PIXEL);
    Write(output, COMPRESSION);
    Write(output, raw_bitmap_size);
    Write(output, HORIZONTAL_RESOLUTION);
    Write(output, VERTICAL_RESOLUTION);
    Write(output, PALETTE_COLOR_NUMBER);
    Write(output, IMPORTANT_COLORS);
    // Pixel Array
    for (size_t row = 0; row < image_height; ++row) {
        for (size_t col = 0; col < image_width; ++col) {
            Write(output, image.GetPixel(col, row));
        }
        WriteZeros(output, bitmap_row_padding);
    }
    output.close();
}
