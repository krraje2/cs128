#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
size_t Width() const;
size_t Height() const;
unsigned int MaxColorValue() const;
const std::vector<Path>& Paths() const;
const std::vector<std::vector<Color> >& GetPathImage() const;
void ToPpm(const std::string& name) const;
size_t MinVal(size_t d1, size_t d2, size_t d3) const;
void ColorSettings();
Path FindPath(const ElevationDataset& dataset, size_t r) const;
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif