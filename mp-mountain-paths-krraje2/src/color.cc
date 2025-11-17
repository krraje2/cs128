#include "color.hpp"

#include <iostream>
const int kMinVal = 0;
const int kMaxVal = 255;
Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r > kMaxVal || r < kMinVal || g > kMaxVal || g < kMinVal || b > kMaxVal ||
      b < kMinVal) {
    throw std::invalid_argument("Value out of possible range");
  }
}

int Color::Red() const { return red_; }

int Color::Blue() const { return blue_; }

int Color::Green() const { return green_; }

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}