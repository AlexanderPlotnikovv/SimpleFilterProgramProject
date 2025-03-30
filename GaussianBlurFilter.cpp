#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    if (sigma < 0) {
        throw std::invalid_argument("Sigma parameter must be non negative!");
    }
    size_t kernel_size = 2 * static_cast<size_t>(std::ceil(3 * sigma)) + 1;
    int32_t radius = static_cast<int32_t>(kernel_size - 1) / 2;
    kernel_.resize(kernel_size);
    for (int32_t i = -radius; i <= radius; ++i) {
        kernel_[i + radius] = 1 / (std::sqrt(2 * math::PI) * sigma) * std::exp(-(i * i) / (2 * sigma * sigma));
    }
}

void GaussianBlurFilter::DoFilter(ImageBMP& image) {
    ImageBMP image_copy = ImageBMP(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            int32_t x = static_cast<int32_t>(j);
            int32_t y = static_cast<int32_t>(i);
            ColorBMP& color_copy = image_copy.At(y, x);
            int32_t radius = static_cast<int32_t>(kernel_.size() - 1) / 2;
            for (int32_t k = -radius; k <= radius; ++k) {
                color_copy = color_copy + image.At(y, x + k) * kernel_[k + radius];
            }
        }
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            int32_t x = static_cast<int32_t>(j);
            int32_t y = static_cast<int32_t>(i);
            ColorBMP color = ColorBMP();
            int32_t radius = static_cast<int32_t>(kernel_.size() - 1) / 2;
            for (int32_t k = -radius; k <= radius; ++k) {
                color = color + image_copy.At(y + k, x) * kernel_[k + radius];
            }
            color = ColorBMP(std::min(color.GetFirstColor(), 1.0), std::min(color.GetSecondColor(), 1.0),
                             std::min(color.GetThirdColor(), 1.0));
            color = ColorBMP(std::max(color.GetFirstColor(), 0.0), std::max(color.GetSecondColor(), 0.0),
                             std::max(color.GetThirdColor(), 0.0));
            image.At(y, x) = color;
        }
    }
}
