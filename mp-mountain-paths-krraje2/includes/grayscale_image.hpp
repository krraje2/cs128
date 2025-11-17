#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const Color& ColorAt(int row, int col) const;
  const std::vector<std::vector<Color>>& GetImage() const;
  void ToPpm(const std::string& name) const;
  int MaxVal(std::vector<std::vector<int>> data) const;
  int MinVal(std::vector<std::vector<int>> data) const;
  //std::vector<std::vector<int>> DataSet(const std::string& filename) const;

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
};

#endif