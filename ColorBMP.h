#pragma once

#include <cstdint>

class ColorBMP {
public:
    explicit ColorBMP(double first_color = 0, double second_color = 0, double third_color = 0);
    ColorBMP(const ColorBMP& color);
    ColorBMP& operator=(const ColorBMP& other);
    ColorBMP operator+(const ColorBMP& other) const;
    ColorBMP operator*(double lambda) const;
    double GetFirstColor() const;
    double GetSecondColor() const;
    double GetThirdColor() const;

private:
    double first_color_;
    double second_color_;
    double third_color_;
};