#pragma once

#include "Filter.h"

class HalftoneFilter : public Filter {
public:
    explicit HalftoneFilter(size_t cell_size);
    void DoFilter(ImageBMP& image) override;

private:
    size_t cell_size_;
};
