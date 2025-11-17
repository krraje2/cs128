#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
std::vector<std::vector<std::string>> PopulateDatabase(std::string& file);
int STRCount(std::string& str, std::string& DNASeq);
std::string MatchTheDNA(std::string DNASeq, std::string file);
std::vector<int> Counts(std::string& DNASeq, std::vector<std::vector<std::string>> data);
std::vector<std::string> Names(std::vector<int> counts, std::vector<std::vector<std::string>> data);
#endif