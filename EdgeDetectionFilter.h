#pragma once

#include "Filter.h"
#include "GrayscaleFilter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold = 1.0);
    void DoFilter(ImageBMP& image) override;

private:
    double threshold_;
};
