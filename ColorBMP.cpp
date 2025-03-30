#include "ColorBMP.h"

ColorBMP::ColorBMP(double first_color, double second_color, double third_color)
    : first_color_(first_color), second_color_(second_color), third_color_(third_color) {
}

ColorBMP::ColorBMP(const ColorBMP& color)
    : first_color_(color.GetFirstColor()), second_color_(color.GetSecondColor()), third_color_(color.GetThirdColor()) {
}

ColorBMP& ColorBMP::operator=(const ColorBMP& other) {
    first_color_ = other.first_color_;
    second_color_ = other.second_color_;
    third_color_ = other.third_color_;
    return *this;
}

ColorBMP ColorBMP::operator+(const ColorBMP& other) const {
    ColorBMP color;
    color.first_color_ = first_color_ + other.first_color_;
    color.second_color_ = second_color_ + other.second_color_;
    color.third_color_ = third_color_ + other.third_color_;
    return color;
}

ColorBMP ColorBMP::operator*(double lambda) const {
    ColorBMP color(*this);
    color.first_color_ *= lambda;
    color.second_color_ *= lambda;
    color.third_color_ *= lambda;
    return color;
}

double ColorBMP::GetFirstColor() const {
    return first_color_;
}

double ColorBMP::GetSecondColor() const {
    return second_color_;
}

double ColorBMP::GetThirdColor() const {
    return third_color_;
}