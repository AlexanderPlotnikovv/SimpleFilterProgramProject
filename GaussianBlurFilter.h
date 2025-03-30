#pragma once

#include "Filter.h"

namespace math {
const double PI = std::acos(-1.0);
}

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma = 1.0);
    void DoFilter(ImageBMP& image) override;

private:
    std::vector<double> kernel_;
};
