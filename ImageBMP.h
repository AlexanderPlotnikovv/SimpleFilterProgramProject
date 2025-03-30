#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "ColorBMP.h"

class ImageBMP {
public:
    explicit ImageBMP(std::vector<std::vector<ColorBMP> >&& pixels);
    explicit ImageBMP(size_t height = 1, size_t width = 1);
    ImageBMP(const ImageBMP& other);
    ImageBMP& operator=(const ImageBMP& other);
    ColorBMP& At(int32_t row, int32_t col);
    void Resize(size_t height, size_t width);
    size_t GetHeight() const;
    size_t GetWidth() const;

private:
    std::vector<std::vector<ColorBMP> > pixels_;
    size_t height_;
    size_t width_;
};