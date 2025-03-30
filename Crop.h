#pragma once

#include "Filter.h"

class Crop : public Filter {
public:
    explicit Crop(size_t width, size_t height);
    void DoFilter(ImageBMP& image) override;

private:
    size_t width_;
    size_t height_;
};