#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "ImageBMP.h"

namespace grayscale_numbers {
const double FIRST = 0.114;
const double SECOND = 0.587;
const double THIRD = 0.299;
}  // namespace grayscale_numbers

class Filter {
public:
    explicit Filter() = default;
    virtual void DoFilter(ImageBMP& image) = 0;
    virtual ~Filter() = default;
};
