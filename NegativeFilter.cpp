#include "NegativeFilter.h"

void NegativeFilter::DoFilter(ImageBMP& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorBMP& color = image.At(static_cast<int32_t>(i), static_cast<int32_t>(j));
            color = ColorBMP(1.0 - color.GetFirstColor(), 1.0 - color.GetSecondColor(), 1.0 - color.GetThirdColor());
        }
    }
}
