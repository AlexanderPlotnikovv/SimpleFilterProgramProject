cmake_minimum_required(VERSION 3.10)

project(image_processor)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wimplicit-fallthrough -g -fsanitize=address,undefined -fno-sanitize-recover=all -std=gnu++20")

add_executable(
        image_processor
        image_processor.cpp
        ColorBMP.cpp
        ColorBMP.h
        ImageBMP.cpp
        ImageBMP.h
        LoadSaveBMP.cpp
        LoadSaveBMP.h
        Filter.cpp
        Filter.h
        NegativeFilter.cpp
        NegativeFilter.h
        GrayscaleFilter.cpp
        GrayscaleFilter.h
        Crop.cpp
        Crop.h
        SharpeningFilter.cpp
        SharpeningFilter.h
        EdgeDetectionFilter.cpp
        EdgeDetectionFilter.h
        GaussianBlurFilter.cpp
        GaussianBlurFilter.h
        HalftoneFilter.cpp
        HalftoneFilter.h
        Controller.cpp
        Controller.h
)