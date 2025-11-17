#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <cassert>
#include <catch/catch.hpp>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

std::string file = "data.dat";
TEST_CASE("STR Checker", "[STR]") {
  std::string dna =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  std::string str = "AGATG";
  REQUIRE(STRCount(str, dna) == 5);
  std::string s2 = "AATG";
  REQUIRE(STRCount(s2, dna) == 2);
  std::string s3 = "TAT";
  REQUIRE(STRCount(s3, dna) == 8);
}

TEST_CASE("Populating the database", "[DATA]") {
  std::string name = "Names";
  REQUIRE(PopulateDatabase(file).at(0).at(0) == name);
}

TEST_CASE("Counts checker", "[COUNT]") {
  std::string dna =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  REQUIRE(Counts(dna, PopulateDatabase(file)).at(0) == 5);
  REQUIRE(Counts(dna, PopulateDatabase(file)).at(1) == 2);
  REQUIRE(Counts(dna, PopulateDatabase(file)).at(2) == 8);
}

TEST_CASE("Names checker", "[NAMES]") {
  std::string dna =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  REQUIRE(Names(Counts(dna, PopulateDatabase(file)), PopulateDatabase(file)).at(0) ==
          "Casey");
}

TEST_CASE("DNA Checker", "[DNA]") {
  std::string dna =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  REQUIRE(MatchTheDNA(dna, file) == "Casey");
  std::string dna2 =
      "TATTATTATTATAACCCTGCGCGCGCGCGATCCAGCATTAGCTAGCATCAAGATGAGATGAGATGGAATTTCGAAATGAATGAATGAATGAATGAATGAATG";
  REQUIRE(MatchTheDNA(dna2, file) == "Amani");
  std::string dna3 =
      "GGTACAGATGGCAAAGATGAGATGAGATGGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGAATGACACACGTCGATGCTAGCGGCGGATCGTATATTATAACCCCTAG";
  REQUIRE(MatchTheDNA(dna3, file) == "no match");
}
