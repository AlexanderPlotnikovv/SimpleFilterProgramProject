#include <iostream>
#include <stdexcept>
#include <string>

#include "Controller.h"

int main(int argc, char** argv) {
    std::vector<std::string> parameters(argc);
    for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        parameters[i] = argv[i];
    }
    try {
        Controller controller(parameters);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
