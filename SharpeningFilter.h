#pragma once

#include "Filter.h"

class SharpeningFilter : public Filter {
public:
    SharpeningFilter() = default;
    void DoFilter(ImageBMP& image) override;
};
