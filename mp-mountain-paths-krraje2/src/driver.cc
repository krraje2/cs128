#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
int main() {
    ElevationDataset e("/home/vagrant/src/mp-mountain-paths-krraje2/src/test.csv", 5, 2);
    GrayscaleImage g(e);
    PathImage p(g ,e);
    
}