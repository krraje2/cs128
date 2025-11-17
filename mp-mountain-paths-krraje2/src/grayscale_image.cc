#include "grayscale_image.hpp"

#include <fstream>
#include <iostream>

#include "elevation_dataset.hpp"
const int kMax = 255;
// std::vector<std::vector<Color>> grayscale;
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  const std::vector<std::vector<int>>& data = dataset.GetData();
  height_ = dataset.Height();
  width_ = dataset.Width();
  for (size_t row = 0; row < height_; row++) {
    std::vector<Color> rows;
    for (size_t col = 0; col < width_; col++) {
      int gray = 0;
      if (dataset.MaxEle() != dataset.MinEle()) {
        double shade_of_gray = std::round(
            (data.at(row).at(col) - static_cast<double>(dataset.MinEle())) /
            (dataset.MaxEle() - dataset.MinEle()) * kMax);
        gray = static_cast<int>(shade_of_gray);
      }
      Color c(gray, gray, gray);
      rows.push_back(c);
    }
    image_.push_back(rows);
  }
  
}
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset e(filename, width, height);
  std::vector<std::vector<int>> data = e.GetData();
  for (size_t row = 0; row < e.Height(); row++) {
    std::vector<Color> rows;
    for (size_t col = 0; col < width_; col++) {
      int gray = 0;
      if (e.MaxEle() != e.MinEle()) {
        double shade_of_gray = std::round(
            (data.at(row).at(col) - static_cast<double>(e.MinEle())) /
            (e.MaxEle() - e.MinEle()) * kMax);
        gray = static_cast<int>(shade_of_gray);
      }
      Color c(gray, gray, gray);
      rows.push_back(c);
    }
    image_.push_back(rows);
  }
}
/* std::vector<std::vector<int>> GrayscaleImage::DataSet(
    const std::string& filename) const {
  std::vector<std::vector<int>> data;
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
    data.push_back(rows);
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
  return data;
} */
int GrayscaleImage::MinVal(std::vector<std::vector<int>> data) const {
  int min = data.at(0).at(0);
  for (size_t r = 0; r < height_; r++) {
    for (size_t c = 0; c < width_; c++) {
      if (data.at(r).at(c) < min) {
        min = data.at(r).at(c);
      }
    }
  }
  return min;
}

int GrayscaleImage::MaxVal(std::vector<std::vector<int>> data) const {
  int max = data.at(0).at(0);
  for (size_t r = 0; r < height_; r++) {
    for (size_t c = 0; c < width_; c++) {
      if (data.at(r).at(c) > max) {
        max = data.at(r).at(c);
      }
    }
  }
  return max;
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream os{name};
  // std::ostream& os;
  os << "P3" << '\n';
  os << width_ << " " << height_ << '\n';
  os << kMax << " " << '\n';
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      os << image_.at(row).at(col).Red() << " "
         << image_.at(row).at(col).Green() << " "
         << image_.at(row).at(col).Blue() << " ";
    }
    os << '\n';
  }
  os << '\n';
}
