#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs{filename};
  std::ifstream ifs2{filename};
  // size_t count = 0;
  for (size_t row = 0; row < height_; row++) {
    std::vector<int> rows;
    for (size_t col = 0; col < width_; col++) {
      int val = -1;
      ifs >> val;
      rows.push_back(val);
      // count++;
    }
    data_.push_back(rows);
  }
  int holder = -1;
  int count = 0;
  while (ifs2 >> holder) {
    count++;
  }
  if (count < static_cast<int>(width_ * height_)) {
    throw std::invalid_argument("Not enough data points");
  }
  if (count > static_cast<int>(width_ * height_)) {
    throw std::invalid_argument("Too many data points");
  }
  min_ele_ = MinVal();
  max_ele_ = MaxVal();
}

int ElevationDataset::MinVal() {
  int min = data_.at(0).at(0);
  for (size_t r = 0; r < height_; r++) {
    for (size_t c = 0; c < width_; c++) {
      if (data_.at(r).at(c) < min) {
        min = data_.at(r).at(c);
      }
    }
  }
  return min;
}

int ElevationDataset::MaxVal() {
  int max = data_.at(0).at(0);
  for (size_t r = 0; r < height_; r++) {
    for (size_t c = 0; c < width_; c++) {
      if (data_.at(r).at(c) > max) {
        max = data_.at(r).at(c);
      }
    }
  }
  return max;
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
