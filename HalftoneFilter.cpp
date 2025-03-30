#include "HalftoneFilter.h"

HalftoneFilter::HalftoneFilter(size_t cell_size) : cell_size_(cell_size) {
    if (cell_size_ <= 0) {
        throw std::invalid_argument("Size of cell never less than 1!");
    }
}

void HalftoneFilter::DoFilter(ImageBMP& image) {
    int32_t max_radius = static_cast<int32_t>(cell_size_) / 2;
    for (size_t i = 0; i < image.GetHeight(); i += cell_size_) {
        for (size_t j = 0; j < image.GetWidth(); j += cell_size_) {
            int32_t x = static_cast<int32_t>(j);
            int32_t y = static_cast<int32_t>(i);
            double avg_brightness = 0;
            for (size_t x_coordinate = x; x_coordinate < static_cast<size_t>(x) + cell_size_; ++x_coordinate) {
                for (size_t y_coordinate = y; y_coordinate < static_cast<size_t>(y) + cell_size_; ++y_coordinate) {
                    double gray = grayscale_numbers::FIRST *
                                      image.At(static_cast<int32_t>(y_coordinate), static_cast<int32_t>(x_coordinate))
                                          .GetFirstColor() +
                                  grayscale_numbers::SECOND *
                                      image.At(static_cast<int32_t>(y_coordinate), static_cast<int32_t>(x_coordinate))
                                          .GetSecondColor() +
                                  grayscale_numbers::THIRD *
                                      image.At(static_cast<int32_t>(y_coordinate), static_cast<int32_t>(x_coordinate))
                                          .GetThirdColor();
                    avg_brightness += gray;
                }
            }
            avg_brightness /= static_cast<double>(cell_size_ * cell_size_);
            int32_t real_radius = static_cast<int32_t>(static_cast<double>(max_radius) * (1.0 - avg_brightness));
            real_radius = std::max(0, std::min(real_radius, max_radius));
            std::pair<int32_t, int32_t> center = {(2 * x + static_cast<int32_t>(cell_size_)) / 2,
                                                  (2 * y + static_cast<int32_t>(cell_size_)) / 2};
            for (size_t x_coordinate = x; x_coordinate < static_cast<size_t>(x) + cell_size_; ++x_coordinate) {
                for (size_t y_coordinate = y; y_coordinate < static_cast<size_t>(y) + cell_size_; ++y_coordinate) {
                    if ((x_coordinate - center.first) * (x_coordinate - center.first) +
                            (y_coordinate - center.second) * (y_coordinate - center.second) <=
                        real_radius * real_radius) {
                        ColorBMP& color =
                            image.At(static_cast<int32_t>(y_coordinate), static_cast<int32_t>(x_coordinate));
                        color = ColorBMP();
                    } else {
                        ColorBMP& color =
                            image.At(static_cast<int32_t>(y_coordinate), static_cast<int32_t>(x_coordinate));
                        color = ColorBMP(1.0, 1.0, 1.0);
                    }
                }
            }
        }
    }
}
