#include <iostream>

#include "roster.hpp"

int main() {
  Roster r;
  r.AddStudent("a");
  r.AddStudent("b");
  r.AddStudent("cca");

  for (auto const& student : r) {
    std::cout << student << std::endl;
  }

  return 0;
}

/*
Professor Amato
Professor Evans
Professor Fleck
Professor Nowak
*/
