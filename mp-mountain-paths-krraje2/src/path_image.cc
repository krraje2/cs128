#include "path_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
// const size_t kLarge = -1;
const int kG1 = 31;
const int kG2 = 253;
const int kG3 = 13;
const int kR1 = 252;
const int kR2 = 25;
const int kR3 = 63;

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    path_image_(image.GetImage()) {
  // std::vector<int> ele_changes;
  // const std::vector<std::vector<int>>& data = dataset.GetData();
  width_ = image.Width();
  height_ = image.Height();
  for (size_t row = 0; row < dataset.Height(); row++) {
    std::cout << row << std::endl;
    Path p = FindPath(dataset, row);
    paths_.push_back(p);
    std::cout << p.EleChange() << std::endl;
    // ele_changes.push_back(p.EleChange());
  }
  ColorSettings();
}
Path PathImage::FindPath(const ElevationDataset& dataset, size_t r) const {
  Path p(width_, r);
  p.SetLoc(0, r);
  for (size_t col = 1; col < dataset.Width(); col++) {
    std::cout << col << std::endl;
    std::cout << r << std::endl;
    int focus = dataset.DatumAt(r, col - 1);
    size_t d1 = -1;
    size_t d2 = -1;
    size_t d3 = -1;
    if (r - 1 != std::numeric_limits<size_t>::max()) {
      d1 = abs(focus - dataset.DatumAt(r - 1, col));
    }
    d2 = abs(focus - dataset.DatumAt(r, col));
    if (r + 1 < dataset.Height()) {
      d3 = abs(focus - dataset.DatumAt(r + 1, col));
    }
    std::cout << MinVal(d1, d2, d3) << std::endl;
    if (MinVal(d1, d2, d3) == d2) {
      p.IncEleChange(d2);
    } else if (MinVal(d1, d2, d3) == d3) {
      r = r + 1;
      p.IncEleChange(d3);
    } else {
      r = r - 1;
      p.IncEleChange(d1);
    }
    p.SetLoc(col, r);
  }
  return p;
}
size_t PathImage::MinVal(size_t d1, size_t d2, size_t d3) const {
  std::vector<size_t> changes = {d1, d2, d3};
  size_t min = d1;
  for (size_t c = 0; c < changes.size(); c++) {
    if (changes.at(c) < min) {
      min = changes.at(c);
    }
  }
  return min;
}

void PathImage::ColorSettings() {
  Path best_row_path = paths_.at(0);
  for (size_t row = 0; row < paths_.size(); row++) {
    if (paths_.at(row).EleChange() < best_row_path.EleChange()) {
      best_row_path = paths_.at(row);
    }
  }
  for (size_t row = 0; row < paths_.size(); row++) {
    Path p = paths_.at(row);
    for (size_t col = 0; col < paths_.at(0).Length(); col++) {
      size_t r = p.GetPath().at(col);
      std::cout << r << std::endl;
      path_image_.at(r).at(col) = Color(kR1, kR2, kR3);
    }
  }
  for (size_t col = 0; col < paths_.at(0).Length(); col++) {
    size_t r = best_row_path.GetPath().at(col);
    path_image_.at(r).at(col) = Color(kG1, kG2, kG3);
  }
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream os{name};
  // std::ostream& os;
  os << "P3" << '\n';
  os << width_ << " " << height_ << '\n';
  os << kMaxColorValue << " " << '\n';
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      os << path_image_.at(row).at(col).Red() << " "
         << path_image_.at(row).at(col).Green() << " "
         << path_image_.at(row).at(col).Blue() << " ";
    }
    os << '\n';
  }
  os << '\n';
}
