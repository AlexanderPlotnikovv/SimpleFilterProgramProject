#pragma once
#include "Filter.h"

class NegativeFilter : public Filter {
public:
    explicit NegativeFilter() = default;
    void DoFilter(ImageBMP& image) override;
};
