#pragma once

#include <cstdint>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include "ImageBMP.h"

#pragma pack(push, 1)
struct BitmapFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_first_reserved;
    uint16_t bf_second_reserved;
    uint32_t bf_off_bits;
};

struct BitmapInfoHeader {
    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_per_meter;
    int32_t bi_y_per_meter;
    uint32_t bi_color_used;
    uint32_t bi_color_important;
};
#pragma pack(pop)

class LoadSaveBMP {
public:
    explicit LoadSaveBMP(const std::string& file_name);
    void Load(const std::string& file_name);
    void Save(const std::string& file_name);
    ImageBMP& GetImage();

private:
    size_t width_;
    size_t height_;
    std::unique_ptr<ImageBMP> image_;
    BitmapFileHeader bitmap_file_header_;
    BitmapInfoHeader bitmap_info_header_;
};