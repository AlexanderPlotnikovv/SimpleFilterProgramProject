#pragma once
#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    explicit GrayscaleFilter() = default;
    void DoFilter(ImageBMP& image) override;
};
