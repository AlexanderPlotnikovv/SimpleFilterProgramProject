#include "Crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

void Crop::DoFilter(ImageBMP& image) {
    width_ = std::min(width_, image.GetWidth());
    height_ = std::min(height_, image.GetHeight());
    image.Resize(height_, width_);
}
