#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Crop.h"
#include "EdgeDetectionFilter.h"
#include "Filter.h"
#include "GaussianBlurFilter.h"
#include "GrayscaleFilter.h"
#include "HalftoneFilter.h"
#include "ImageBMP.h"
#include "LoadSaveBMP.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"

class Controller {
public:
    explicit Controller(const std::vector<std::string>& parameters);

private:
    std::string input_file_;
    std::unique_ptr<Filter> filter_;
    std::string output_file_;
    bool IsNumber(const std::string& s);
};
