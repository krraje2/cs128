#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY
const int kMax = 2147483647;
SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  return ColTotal(row, col) + RowTotal(row, col);
}

int SeamCarver::ColTotal(int row, int col) const {
  int reds1 = 0;
  int greens1 = 0;
  int blues1 = 0;
  if (col == 0) {
    reds1 = image_.GetPixel(row, width_ - 1).GetRed() -
            image_.GetPixel(row, col + 1).GetRed();
    greens1 = image_.GetPixel(row, width_ - 1).GetGreen() -
              image_.GetPixel(row, col + 1).GetGreen();
    blues1 = image_.GetPixel(row, width_ - 1).GetBlue() -
             image_.GetPixel(row, col + 1).GetBlue();
  } else if (col == width_ - 1) {
    reds1 = image_.GetPixel(row, col - 1).GetRed() -
            image_.GetPixel(row, 0).GetRed();
    greens1 = image_.GetPixel(row, col - 1).GetGreen() -
              image_.GetPixel(row, 0).GetGreen();
    blues1 = image_.GetPixel(row, col - 1).GetBlue() -
             image_.GetPixel(row, 0).GetBlue();
  } else {
    reds1 = image_.GetPixel(row, col - 1).GetRed() -
            image_.GetPixel(row, col + 1).GetRed();
    greens1 = image_.GetPixel(row, col - 1).GetGreen() -
              image_.GetPixel(row, col + 1).GetGreen();
    blues1 = image_.GetPixel(row, col - 1).GetBlue() -
             image_.GetPixel(row, col + 1).GetBlue();
  }
  return reds1 * reds1 + greens1 * greens1 + blues1 * blues1;
}
int SeamCarver::RowTotal(int row, int col) const {
  int reds1 = 0;
  int greens1 = 0;
  int blues1 = 0;
  if (row == 0) {
    reds1 = image_.GetPixel(height_ - 1, col).GetRed() -
            image_.GetPixel(row + 1, col).GetRed();
    greens1 = image_.GetPixel(height_ - 1, col).GetGreen() -
              image_.GetPixel(row + 1, col).GetGreen();
    blues1 = image_.GetPixel(height_ - 1, col).GetBlue() -
             image_.GetPixel(row + 1, col).GetBlue();
  } else if (row == height_ - 1) {
    reds1 = image_.GetPixel(row - 1, col).GetRed() -
            image_.GetPixel(0, col).GetRed();
    greens1 = image_.GetPixel(row - 1, col).GetGreen() -
              image_.GetPixel(0, col).GetGreen();
    blues1 = image_.GetPixel(row - 1, col).GetBlue() -
             image_.GetPixel(0, col).GetBlue();
  } else {
    reds1 = image_.GetPixel(row - 1, col).GetRed() -
            image_.GetPixel(row + 1, col).GetRed();
    greens1 = image_.GetPixel(row - 1, col).GetGreen() -
              image_.GetPixel(row + 1, col).GetGreen();
    blues1 = image_.GetPixel(row - 1, col).GetBlue() -
             image_.GetPixel(row + 1, col).GetBlue();
  }
  return reds1 * reds1 + greens1 * greens1 + blues1 * blues1;
}

int SeamCarver::MinVal(int d1, int d2, int d3) const {
  int changes[] = {d1, d2, d3};
  int min = d1;
  for (int row = 0; row < 3; row++) {
    if (changes[row] < min) {
      min = changes[row];
    }
  }
  return min;
}
int* SeamCarver::GetHorizontalSeam() const {
  int** horarr = HorizontalCalculating();
  int* horseam = new int[width_];
  int min = kMax;
  int row_index = 0;
  for (int row = height_ - 1; row >= 0; row--) {
    if (horarr[row][0] <= min) {
      min = horarr[row][0];
      row_index = row;
    }
  }
  horseam[0] = row_index;
  for (int col = 1; col < width_; col++) {
    int d1 = kMax;
    int d2 = kMax;
    int d3 = kMax;
    if (row_index - 1 >= 0) {
      d1 = horarr[row_index - 1][col];
    }
    if (row_index + 1 < height_) {
      d2 = horarr[row_index + 1][col];
    }
    d3 = horarr[row_index][col];
    if (MinVal(d1, d2, d3) == d3) {
      int holder = row_index;
      row_index = holder;
    } else if (MinVal(d1, d2, d3) == d1) {
      row_index = row_index - 1;
    } else {
      row_index = row_index + 1;
    }
    horseam[col] = row_index;
  }

  for (int row = 0; row < height_; row++) {
    delete[] horarr[row];
  }
  delete[] horarr;
  horarr = nullptr;
  return horseam;
}
int* SeamCarver::GetVerticalSeam() const {
  int** vertarr = VerticalCalculating();
  int* verseam = new int[height_];
  int min = kMax;
  int col_index = 0;
  for (int col = width_ - 1; col >= 0; col--) {
    if (vertarr[0][col] <= min) {
      min = vertarr[0][col];
      col_index = col;
    }
  }
  verseam[0] = col_index;
  for (int row = 1; row < height_; row++) {
    int d1 = kMax;
    int d2 = kMax;
    int d3 = kMax;
    if (col_index - 1 >= 0) {
      d1 = vertarr[row][col_index - 1];
    }
    if (col_index + 1 < width_) {
      d2 = vertarr[row][col_index + 1];
    }
    d3 = vertarr[row][col_index];
    if (MinVal(d1, d2, d3) == d3) {
      int holder = col_index;
      col_index = holder;
    } else if (MinVal(d1, d2, d3) == d1) {
      col_index = col_index - 1;
    } else {
      col_index = col_index + 1;
    }
    verseam[row] = col_index;
  }

for (int row = 0; row < height_; row++) {
  delete[] vertarr[row];
}
delete[] vertarr;
vertarr = nullptr;
return verseam;
}
int** SeamCarver::VerticalCalculating() const {
  // setting 2d array with energy values
  int** arr = new int*[height_];
  for (int row = 0; row < height_; row++) {
    arr[row] = new int[width_];
  }
  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col++) {
      arr[row][col] = GetEnergy(row, col);
    }
  }
  // reseting for vertical seam
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int d1 = kMax;
      int d2 = kMax;
      int d3 = kMax;
      int focus = arr[row][col];
      if (col - 1 >= 0) {
        d1 = arr[row + 1][col - 1];
      }
      if (col + 1 < width_) {
        d2 = arr[row + 1][col + 1];
      }
      d3 = arr[row + 1][col];
      int min = MinVal(d1, d2, d3);
      arr[row][col] = focus + min;
    }
  }
  return arr;
}

int** SeamCarver::HorizontalCalculating() const {
  // setting 2d array with energy values
  int** arr = new int*[height_];
  for (int row = 0; row < height_; row++) {
    arr[row] = new int[width_];
  }
  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col++) {
      arr[row][col] = GetEnergy(row, col);
    }
  }
  // reseting for horizontal seam
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      int d1 = kMax;
      int d2 = kMax;
      int d3 = kMax;
      int focus = arr[row][col];
      if (row - 1 >= 0) {
        d1 = arr[row - 1][col + 1];
      }
      if (row + 1 < height_) {
        d2 = arr[row + 1][col + 1];
      }
      d3 = arr[row][col + 1];
      int min = MinVal(d1, d2, d3);
      arr[row][col] = focus + min;
    }
  }
  return arr;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* horseam = GetHorizontalSeam();
  image_.HorizontalCarver(horseam);
  height_ = image_.GetHeight();
  delete[] horseam;
  horseam = nullptr;
}

void SeamCarver::RemoveVerticalSeam() {
  int* vertseam = GetVerticalSeam();
  image_.VerticalCarver(vertseam);
  width_ = image_.GetWidth();
  delete[] vertseam;
  vertseam = nullptr;
}
