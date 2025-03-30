#include "LoadSaveBMP.h"

LoadSaveBMP::LoadSaveBMP(const std::string& file_name) : width_(0), height_(0), image_(nullptr) {
    Load(file_name);
}

void LoadSaveBMP::Load(const std::string& file_name) {
    const uint16_t bf_type = 19778;
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Enter existing file!");
    }
    file.read(reinterpret_cast<char*>(&bitmap_file_header_), sizeof(BitmapFileHeader));
    if (bitmap_file_header_.bf_type != bf_type) {
        throw std::runtime_error("Enter bmp file!");
    }
    if (bitmap_file_header_.bf_size <= sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)) {
        throw std::runtime_error("Invalid file!");
    }
    file.read(reinterpret_cast<char*>(&bitmap_info_header_), sizeof(BitmapInfoHeader));
    width_ = bitmap_info_header_.bi_width;
    height_ = std::abs(bitmap_info_header_.bi_height);
    std::vector<std::vector<ColorBMP> > color_matrix(height_, std::vector<ColorBMP>(width_));

    size_t bytes_in_row = static_cast<int32_t>(width_ * 3 + 3) / 4 * 4;
    std::vector<uint8_t> row(bytes_in_row);

    for (size_t i = 0; i < height_; ++i) {
        file.read(reinterpret_cast<char*>(row.data()), static_cast<std::streamsize>(bytes_in_row));
        for (size_t j = 0; j < width_ * 3; j += 3) {
            uint8_t first_color = row[j];
            uint8_t second_color = row[j + 1];
            uint8_t third_color = row[j + 2];
            if (bitmap_info_header_.bi_height < 0) {
                color_matrix[i][j / 3] = ColorBMP(
                    static_cast<double>(first_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                    static_cast<double>(second_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                    static_cast<double>(third_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()));
            } else {
                color_matrix[height_ - 1 - i][j / 3] = ColorBMP(
                    static_cast<double>(first_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                    static_cast<double>(second_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                    static_cast<double>(third_color) / static_cast<double>(std::numeric_limits<uint8_t>::max()));
            }
        }
    }
    file.close();
    image_ = std::make_unique<ImageBMP>(std::move(color_matrix));
}

void LoadSaveBMP::Save(const std::string& file_name) {
    height_ = image_->GetHeight();
    width_ = image_->GetWidth();
    size_t bytes_in_row = static_cast<int32_t>(width_ * 3 + 3) / 4 * 4;
    std::ofstream file(file_name, std::ios::binary);
    bitmap_file_header_.bf_size = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + 3 * (bytes_in_row * height_);
    bitmap_info_header_.bi_height = static_cast<int32_t>(height_);
    bitmap_info_header_.bi_width = static_cast<int32_t>(width_);
    file.write(reinterpret_cast<char*>(&bitmap_file_header_), sizeof(BitmapFileHeader));
    file.write(reinterpret_cast<char*>(&bitmap_info_header_), sizeof(BitmapInfoHeader));
    std::vector<uint8_t> row(bytes_in_row);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < 3 * width_; j += 3) {
            row[j] = static_cast<uint8_t>(
                image_->At(static_cast<int32_t>(height_ - 1 - i), static_cast<int32_t>(j / 3)).GetFirstColor() *
                static_cast<double>(std::numeric_limits<uint8_t>::max()));
            row[j + 1] = static_cast<uint8_t>(
                image_->At(static_cast<int32_t>(height_ - 1 - i), static_cast<int32_t>(j / 3)).GetSecondColor() *
                static_cast<double>(std::numeric_limits<uint8_t>::max()));
            row[j + 2] = static_cast<uint8_t>(
                image_->At(static_cast<int32_t>(height_ - 1 - i), static_cast<int32_t>(j / 3)).GetThirdColor() *
                static_cast<double>(std::numeric_limits<uint8_t>::max()));
        }
        for (size_t j = 3 * width_; j < bytes_in_row; ++j) {
            row[j] = 0x00;
        }
        file.write(reinterpret_cast<char*>(row.data()), static_cast<std::streamsize>(bytes_in_row));
    }
}

ImageBMP& LoadSaveBMP::GetImage() {
    return *image_;
}