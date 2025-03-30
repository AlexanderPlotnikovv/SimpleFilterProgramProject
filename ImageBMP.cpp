#include "ImageBMP.h"

ImageBMP::ImageBMP(std::vector<std::vector<ColorBMP> >&& pixels) : pixels_(std::move(pixels)) {
    height_ = pixels_.size();
    width_ = pixels_[0].size();
    if (height_ == 0 || width_ == 0) {
        throw std::runtime_error("Empty image!");
    }
}

ImageBMP::ImageBMP(size_t height, size_t width)
    : pixels_(height, std::vector<ColorBMP>(width, ColorBMP())), height_(height), width_(width) {
    if (height_ == 0 || width_ == 0) {
        throw std::runtime_error("Empty image!");
    }
}

ImageBMP::ImageBMP(const ImageBMP& other)
    : pixels_(other.pixels_), height_(other.GetHeight()), width_(other.GetWidth()) {
    if (height_ == 0 || width_ == 0) {
        throw std::runtime_error("Empty image!");
    }
}

ImageBMP& ImageBMP::operator=(const ImageBMP& other) {
    Resize(other.GetHeight(), other.GetWidth());
    pixels_ = other.pixels_;
    return *this;
}

ColorBMP& ImageBMP::At(int32_t row, int32_t col) {
    row = std::max(row, 0);
    col = std::max(col, 0);
    row = std::min(row, static_cast<int32_t>(height_) - 1);
    col = std::min(col, static_cast<int32_t>(width_) - 1);
    return pixels_[row][col];
}

void ImageBMP::Resize(size_t height, size_t width) {
    pixels_.resize(height);
    for (auto& row : pixels_) {
        row.resize(width);
    }
    height_ = height;
    width_ = width;
    if (height_ == 0 || width_ == 0) {
        throw std::runtime_error("Empty image!");
    }
}

size_t ImageBMP::GetHeight() const {
    return height_;
}

size_t ImageBMP::GetWidth() const {
    return width_;
}