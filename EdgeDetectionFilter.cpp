#include "EdgeDetectionFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {
    if (threshold < 0) {
        throw std::invalid_argument("Threshold parameter must be non negative");
    }
}

void EdgeDetectionFilter::DoFilter(ImageBMP& image) {
    std::unique_ptr<Filter> filter = std::make_unique<GrayscaleFilter>();
    filter->DoFilter(image);
    const double edge_detection = 4.0;
    ImageBMP image_copy(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            int32_t y = static_cast<int32_t>(i);
            int32_t x = static_cast<int32_t>(j);
            ColorBMP& color = image_copy.At(y, x);
            color = image.At(y, x - 1) * -1.0 + image.At(y, x + 1) * -1.0 + image.At(y - 1, x) * -1.0 +
                    image.At(y + 1, x) * -1.0 + image.At(y, x) * edge_detection;
            color = ColorBMP(std::min(color.GetFirstColor(), 1.0), std::min(color.GetSecondColor(), 1.0),
                             std::min(color.GetThirdColor(), 1.0));
            color = ColorBMP(std::max(color.GetFirstColor(), 0.0), std::max(color.GetSecondColor(), 0.0),
                             std::max(color.GetThirdColor(), 0.0));
        }
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            ColorBMP& color = image.At(static_cast<int32_t>(i), static_cast<int32_t>(j));
            if (image_copy.At(static_cast<int32_t>(i), static_cast<int32_t>(j)).GetFirstColor() > threshold_) {
                color = ColorBMP(1.0, 1.0, 1.0);
            } else {
                color = ColorBMP();
            }
        }
    }
}
