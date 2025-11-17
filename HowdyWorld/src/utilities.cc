#include "utilities.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::string Howdy(const std::string& name) {
  std::string howdy_name = "Howdy, " + name + "!";
  return howdy_name;
}

std::vector<int> get_ints_from_file(std::string file_name) {
  std::vector<int> vect;
  std::ifstream ifs(file_name);
  if (!(ifs.is_open())) {
    throw std::runtime_error("File is not opening");
  }
  int value = 0;
  while (ifs.good()) {
    ifs >> value;
  if (ifs.fail()) {
  ifs.clear();
  ifs.ignore(1, '\n');
  } else {
  vect.push_back(value);
  }
  
  }
  
  return vect;
}