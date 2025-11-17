#include "functions.hpp"

#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.hpp"

std::vector<std::vector<std::string>> PopulateDatabase(std::string& file) {
  std::vector<std::vector<std::string>> data;
  std::ifstream ifs{file};
  for (std::string line; std::getline(ifs, line); line = "") {
    data.push_back(utilities::GetSubstrs(line, ','));
  }
  return data;
}

int STRCount(std::string& str, std::string& DNASeq) {
  const int kLength = str.length();
  int count = 0;
  int max = 0;
  for (size_t index = 0; index <= DNASeq.length() - kLength; ++index) {
    std::string sub = DNASeq.substr(index, kLength);
    std::string next = DNASeq.substr(index + kLength, kLength);
    for (; next == str; next = DNASeq.substr(index + kLength, kLength)) {
      if (sub == str) {
        ++count;
        sub = next;
        index += kLength;
      } else {
        break;
      }
    }
    if (sub == str) {
      ++count;
    }
    if (max < count) {
      max = count;
    }
    count = 0;
  }
  return max;
}

std::vector<int> Counts(std::string& DNASeq,
                        std::vector<std::vector<std::string>> data) {
  std::vector<int> counts;
  for (size_t i = 1; i < data.at(0).size(); ++i) {
    counts.push_back(STRCount(data.at(0).at(i), DNASeq));
  }
  return counts;
}

std::vector<std::string> Names(std::vector<int> counts,
                               std::vector<std::vector<std::string>> data) {
  std::vector<std::string> names;
  for (size_t row = 1; row < data.size(); ++row) {
    int tracker = 0;
    for (size_t col = 1; col < data.at(0).size(); ++col) {
      if (std::stoi(data.at(row).at(col)) == counts.at(col - 1)) {
        tracker++;
      }
      if (tracker == static_cast<int>(data.at(0).size()) - 1) {
        names.push_back(data.at(row).at(0));
      }
    }
  }
  return names;
}

std::string MatchTheDNA(std::string DNASeq, std::string file) {
  std::vector<std::vector<std::string>> data = PopulateDatabase(file);
  std::vector<int> counts;
  std::vector<std::string> names;
  counts = Counts(DNASeq, data);
  names = Names(counts, data);
  if (names.size() == 1) {
    return names.at(0);
  }
  return "no match";
}
