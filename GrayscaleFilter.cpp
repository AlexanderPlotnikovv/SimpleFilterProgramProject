#include "GrayscaleFilter.h"

void GrayscaleFilter::DoFilter(ImageBMP& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorBMP& color = image.At(static_cast<int32_t>(i), static_cast<int32_t>(j));
            double new_color = grayscale_numbers::FIRST * color.GetFirstColor() +
                               grayscale_numbers::SECOND * color.GetSecondColor() +
                               grayscale_numbers::THIRD * color.GetThirdColor();
            color = ColorBMP(new_color, new_color, new_color);
        }
    }
}
