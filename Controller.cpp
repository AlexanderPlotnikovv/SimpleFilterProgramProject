#include "Controller.h"

bool Controller::IsNumber(const std::string& s) {
    try {
        std::stod(s);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    }
}

Controller::Controller(const std::vector<std::string>& parameters) {
    if (parameters.size() < 3) {
        throw std::invalid_argument("Enter input and output files");
    }
    input_file_ = parameters[1];
    output_file_ = parameters[2];
    LoadSaveBMP loader(input_file_);
    ImageBMP& image = loader.GetImage();
    size_t command_ptr = 3;
    while (command_ptr < parameters.size()) {
        if (parameters[command_ptr] == "-crop") {
            ++command_ptr;
            if (command_ptr == parameters.size()) {
                throw std::out_of_range("Missing necessary arguments");
            }
            if (!IsNumber(parameters[command_ptr])) {
                throw std::invalid_argument("Missing width");
            }
            if (std::stod(parameters[command_ptr]) != static_cast<int32_t>(std::stod(parameters[command_ptr]))) {
                throw std::invalid_argument("Width must be integer");
            }
            size_t width = static_cast<size_t>(std::stoi(parameters[command_ptr]));
            ++command_ptr;
            if (command_ptr == parameters.size()) {
                throw std::out_of_range("Missing necessary arguments");
            }
            if (!IsNumber(parameters[command_ptr])) {
                throw std::invalid_argument("Missing height");
            }
            if (std::stod(parameters[command_ptr]) != static_cast<int32_t>(std::stod(parameters[command_ptr]))) {
                throw std::invalid_argument("Height must be integer");
            }
            size_t height = static_cast<size_t>(std::stoi(parameters[command_ptr]));
            filter_ = std::make_unique<Crop>(width, height);
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-gs") {
            filter_ = std::make_unique<GrayscaleFilter>();
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-neg") {
            filter_ = std::make_unique<NegativeFilter>();
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-sharp") {
            filter_ = std::make_unique<SharpeningFilter>();
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-edge") {
            ++command_ptr;
            if (command_ptr == parameters.size()) {
                throw std::out_of_range("Missing necessary arguments");
            }
            if (!IsNumber(parameters[command_ptr])) {
                throw std::invalid_argument("Missing threshold");
            }
            double threshold = std::stod(parameters[command_ptr]);
            filter_ = std::make_unique<EdgeDetectionFilter>(threshold);
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-blur") {
            ++command_ptr;
            if (command_ptr == parameters.size()) {
                throw std::out_of_range("Missing necessary arguments");
            }
            if (!IsNumber(parameters[command_ptr])) {
                throw std::invalid_argument("Missing sigma");
            }
            double sigma = std::stod(parameters[command_ptr]);
            filter_ = std::make_unique<GaussianBlurFilter>(sigma);
            filter_->DoFilter(image);
        } else if (parameters[command_ptr] == "-ht") {
            ++command_ptr;
            if (command_ptr == parameters.size()) {
                throw std::out_of_range("Missing necessary arguments");
            }
            if (!IsNumber(parameters[command_ptr])) {
                throw std::invalid_argument("Missing cell_size");
            }
            if (std::stod(parameters[command_ptr]) != static_cast<int32_t>(std::stod(parameters[command_ptr]))) {
                throw std::invalid_argument("Cell size must be integer");
            }
            size_t cell_size = static_cast<size_t>(std::stoi(parameters[command_ptr]));
            filter_ = std::make_unique<HalftoneFilter>(cell_size);
            filter_->DoFilter(image);
        } else {
            throw std::invalid_argument("Filter doesn't exist");
        }
        ++command_ptr;
    }
    loader.Save(output_file_);
}
