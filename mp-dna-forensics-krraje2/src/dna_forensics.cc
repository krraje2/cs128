#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::cout << MatchTheDNA(argv[2], argv[1]) << std::endl;

  return 0;
}