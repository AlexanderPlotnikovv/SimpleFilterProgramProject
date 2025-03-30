#include "SharpeningFilter.h"

void SharpeningFilter::DoFilter(ImageBMP& image) {
    const double sharpering_k = 5.0;
    ImageBMP image_copy(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            int32_t y = static_cast<int32_t>(i);
            int32_t x = static_cast<int32_t>(j);
            ColorBMP& color = image_copy.At(y, x);
            color = image.At(y, x - 1) * -1.0 + image.At(y, x + 1) * -1.0 + image.At(y - 1, x) * -1.0 +
                    image.At(y + 1, x) * -1.0 + image.At(y, x) * sharpering_k;
            color = ColorBMP(std::min(color.GetFirstColor(), 1.0), std::min(color.GetSecondColor(), 1.0),
                             std::min(color.GetThirdColor(), 1.0));
            color = ColorBMP(std::max(color.GetFirstColor(), 0.0), std::max(color.GetSecondColor(), 0.0),
                             std::max(color.GetThirdColor(), 0.0));
        }
    }
    image = image_copy;
}
